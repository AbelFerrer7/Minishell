/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:29:48 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/18 17:44:33 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_heredoc_to_pipe(char *delimiter, char **envp)
{
	char	*line;
	char	*expanded_line;
	size_t	delim_len;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (-1);
	delim_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (print_error(NULL, "heredoc delimited by eof")
				, close(pipe_fds[1]), pipe_fds[0]);
		if (ft_strlen(line) == delim_len
			&& ft_strncmp(line, delimiter, delim_len) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_vars_heredoc(line, envp);
		ft_putstr_fd(expanded_line, pipe_fds[1]);
		(ft_putstr_fd("\n", pipe_fds[1]), free(line), free(expanded_line));
	}
	return (close(pipe_fds[1]), pipe_fds[0]);
}

int	setup_heredoc_input(t_cmd *cmd, char **envp)
{
	int	fd;

	if (cmd->heredoc_count > 0)
	{
		if (process_all_heredocs(cmd, envp) == -1)
			return (print_error(NULL, "heredoc failed"), -1);
	}
	else
	{
		fd = read_heredoc_to_pipe(cmd->delimiter, envp);
		if (fd == -1)
		{
			print_error(NULL, "heredoc failed");
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	setup_input_redirection(t_cmd *cmd, char **envp)
{
	int	fd;

	if (cmd->heredoc)
		return (setup_heredoc_input(cmd, envp));
	else if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			print_error(cmd->infile, "No such file or directory");
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	setup_output_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	manage_heredoc(char *delimiter, char **envp)
{
	return (read_heredoc_to_pipe(delimiter, envp));
}
