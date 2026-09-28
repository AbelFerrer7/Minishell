/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:06:16 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/18 16:33:27 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_redirections(t_cmd *cmd, char **envp)
{
	if (setup_input_redirection(cmd, envp) == -1)
		return (-1);
	if (setup_output_redirection(cmd) == -1)
		return (-1);
	return (0);
}

int	wait_and_get_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		if (WTERMSIG(status) == SIGQUIT)
			return (131);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	process_all_heredocs(t_cmd *cmd, char **envp)
{
	int	i;
	int	fd;

	i = 0;
	while (i < cmd->heredoc_count)
	{
		fd = read_heredoc_to_pipe(cmd->heredoc_delimiters[i], envp);
		if (fd == -1)
			return (-1);
		if (i < cmd->heredoc_count - 1)
		{
			close(fd);
		}
		else
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}
