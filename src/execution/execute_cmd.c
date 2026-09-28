/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:25:12 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/13 05:01:04 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_and_clean_args(t_cmd *cmd, char **envp)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmd->args[i])
	{
		temp = cmd->args[i];
		cmd->args[i] = expand_vars(cmd->args[i], envp);
		free(temp);
		temp = cmd->args[i];
		cmd->args[i] = remove_quotes(cmd->args[i]);
		if (cmd->args[i])
			free(temp);
		else
			cmd->args[i] = temp;
		i++;
	}
	check_just_quotes(cmd);
}

static void	process_and_clean_empty_args(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd->args[i] && ft_strlen(cmd->args[i]) == 0)
		i++;
	if (i > 0)
	{
		j = 0;
		while (cmd->args[i])
			cmd->args[j++] = cmd->args[i++];
		cmd->args[j] = NULL;
	}
}

static void	handle_execution_error(char *cmd_name)
{
	struct stat	file_stat;

	if (ft_strchr(cmd_name, '/'))
	{
		if (stat(cmd_name, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				print_error(cmd_name, "Is a directory");
			else
				print_error(cmd_name, "Permission denied");
			exit(126);
		}
		else
		{
			print_error(cmd_name, "No such file or directory");
			exit(127);
		}
	}
	else
	{
		print_error(cmd_name, "command not found");
		exit(127);
	}
}

static void	execute_command_or_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int		exit_code;

	if (is_builtin(cmd->args[0]))
	{
		exit_code = run_builtin(cmd->args, shell);
		exit(exit_code);
	}
	path = find_path(cmd->args[0], shell->envp);
	if (!path)
	{
		handle_execution_error(cmd->args[0]);
	}
	execve(path, cmd->args, shell->envp);
	perror("execve");
	free(path);
	exit(1);
}

int	exec_command(t_cmd *cmd, t_shell *shell)
{
	expand_and_clean_args(cmd, shell->envp);
	process_and_clean_empty_args(cmd);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	execute_command_or_builtin(cmd, shell);
	return (0);
}
