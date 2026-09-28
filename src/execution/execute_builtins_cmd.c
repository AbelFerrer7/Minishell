/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:35:07 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/18 00:53:52 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	stdin_cpy;
	int	stdout_cpy;
	int	exit_code;

	preprocess_args(cmd, shell->envp);
	stdin_cpy = dup(STDIN_FILENO);
	if (stdin_cpy == -1)
		return (1);
	stdout_cpy = dup(STDOUT_FILENO);
	if (stdout_cpy == -1)
		return (close(stdin_cpy), 1);
	if (setup_redirections(cmd, shell->envp) == -1)
	{
		close(stdin_cpy);
		close(stdout_cpy);
		return (1);
	}
	exit_code = run_builtin(cmd->args, shell);
	if (dup2(stdin_cpy, STDIN_FILENO) == -1
		|| dup2(stdout_cpy, STDOUT_FILENO) == -1)
		exit_code = 1;
	close(stdin_cpy);
	close(stdout_cpy);
	return (exit_code);
}

/*
** Punto de entrada principal para ejecución de comandos
** Decide si ejecutar comando único o pipeline según estructura
** Retorna código de salida del último comando ejecutado
*/
int	execute_cmds(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (0);
	if (!cmds->next)
		return (execute_single(cmds, shell));
	execute_pipeline(cmds, shell);
	return (g_exit_status);
}

/*
** Ejecuta un comando individual (sin pipes)
** Expande variables y determina si es builtin o comando externo
** Maneja memoria correctamente liberando strings temporales
*/
int	execute_single(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_name;
	char	*temp;

	if (!cmd->args || !cmd->args[0])
		return (0);
	cmd_name = expand_vars(cmd->args[0], shell->envp);
	temp = cmd_name;
	cmd_name = remove_quotes(cmd_name);
	free(temp);
	if (is_builtin(cmd_name))
	{
		free(cmd_name);
		return (execute_builtin(cmd, shell));
	}
	return (execute_external(cmd, shell, cmd_name));
}

/*
** Ejecuta comando externo en proceso hijo con fork/exec
** Maneja señales correctamente para procesos padre e hijo
** Configura redirecciones antes de exec y espera resultado
*/
int	execute_external(t_cmd *cmd, t_shell *shell, char *cmd_name)
{
	pid_t	pid;
	int		exit_code;

	free(cmd_name);
	ignore_signals();
	pid = fork();
	if (pid == -1)
	{
		setup_signals();
		return (1);
	}
	if (pid == 0)
	{
		restore_signals();
		if (setup_redirections(cmd, shell->envp) == -1)
			exit(1);
		exec_command(cmd, shell);
	}
	setup_signals_executing();
	exit_code = wait_and_get_status(pid);
	setup_signals();
	return (exit_code);
}
