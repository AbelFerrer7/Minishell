/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:51:41 by calguaci          #+#    #+#             */
/*   Updated: 2025/07/18 18:51:10 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	has_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-' || str[1] != 'n')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	run_builtin(char **args, t_shell *shell)
{
	char	*cmd;

	cmd = args[0];
	if (ft_strcmp(cmd, "unset") == 0)
		return (builtin_unset(args[1], shell));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(args, shell));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(args, &shell->envp));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd, "exit") == 0)
		return (builtin_exit(args, shell));
	else if (ft_strcmp(cmd, "export") == 0)
		return (builtin_export(args, shell));
	else if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env(shell->envp));
	return (-1);
}
