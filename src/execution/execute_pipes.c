/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:28:02 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/18 01:06:17 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_pipe_input(int i_fd)
{
	if (i_fd != STDIN_FILENO)
	{
		if (dup2(i_fd, STDIN_FILENO) == -1)
		{
			close(i_fd);
			exit(1);
		}
		close(i_fd);
	}
}

static void	execute_child(t_cmd *cmd, t_shell *shell, int i_fd, int o_fd)
{
	restore_signals();
	setup_pipe_input(i_fd);
	if (cmd->outfile)
	{
		if (o_fd != STDOUT_FILENO)
			close(o_fd);
		if (setup_redirections(cmd, shell->envp) == -1)
			exit(1);
	}
	else
	{
		if (setup_input_redirection(cmd, shell->envp) == -1)
		{
			if (o_fd != STDOUT_FILENO)
				close(o_fd);
			exit(1);
		}
		if (o_fd != STDOUT_FILENO)
		{
			if (dup2(o_fd, STDOUT_FILENO) == -1)
				(close(o_fd), exit(1));
			close(o_fd);
		}
	}
	exec_command(cmd, shell);
}

/*
** Ejecuta un pipeline de dos comandos conectados por pipe
** Crea procesos hijo y maneja file descriptors correctamente
** Cierra FDs inmediatamente después de fork para evitar deadlock
*/
void	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"));
	ignore_signals();
	pid1 = fork();
	if (pid1 == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), perror("fork"));
	if (pid1 == 0)
		(close(pipe_fd[0]),
			execute_child(cmds, shell, STDIN_FILENO, pipe_fd[1]));
	pid2 = fork();
	if (pid2 == -1)
	{
		(close(pipe_fd[0]), close(pipe_fd[1]), kill(pid1, SIGTERM));
		return (waitpid(pid1, NULL, 0), perror("fork"));
	}
	if (pid2 == 0)
		(close(pipe_fd[1]), execute_second_child(cmds, shell, pipe_fd[0]));
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	finalize_pipeline(pid1, pid2, &status, cmds);
}

/*
** Maneja el segundo proceso en un pipeline, soporta pipes múltiples
** Cierra FDs no usados para evitar bloqueos
*/
void	execute_second_child(t_cmd *cmds, t_shell *shell, int input_fd)
{
	if (cmds->next->next)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			close(input_fd);
			exit(1);
		}
		close(input_fd);
		execute_pipeline(cmds->next, shell);
		exit(g_exit_status);
	}
	else
		execute_child(cmds->next, shell, input_fd, STDOUT_FILENO);
}

void	finalize_pipeline(pid_t pid1, pid_t pid2, int *status, t_cmd *cmds)
{
	int	status1;
	int	status2;

	setup_signals_executing();
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	setup_signals();
	if (WIFSIGNALED(status1) && WTERMSIG(status1) == SIGPIPE)
	{
		if (!cmds->next || !cmds->next->outfile)
			ft_putstr_fd("Broken pipe\n", 2);
	}
	*status = status2;
	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
			g_exit_status = 130;
		else if (WTERMSIG(*status) == SIGQUIT)
			g_exit_status = 131;
	}
	else if (WIFEXITED(*status))
	{
		g_exit_status = WEXITSTATUS(*status);
	}
}
