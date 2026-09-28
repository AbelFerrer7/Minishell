/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:51:29 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/12 20:07:58 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (path);
}

int	builtin_pwd(void)
{
	char	*path;

	path = get_pwd();
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(path);
		return (0);
	}
	return (1);
}

int	builtin_unset(char *key, t_shell *shell)
{
	shell->envp = elim_env(shell->envp, key);
	if (!shell->envp)
		return (1);
	return (0);
}

int	builtin_echo(char **args, t_shell *shell)
{
	int	check_flag;
	int	i;

	(void)shell;
	if (!args || !args[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	check_flag = has_flag(args[1]);
	i = 1;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-' && args[i][1] == 'n' && check_flag == 0)
			i++;
		else
			break ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] && args[i + 1][0] != '\0')
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (check_flag == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	builtin_env(char **envp)
{
	int	i;

	if (!envp || !envp[0])
		return (1);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
