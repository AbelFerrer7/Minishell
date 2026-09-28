/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:51:54 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/18 13:21:12 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_val(char *var, char **env)
{
	char	*value;
	char	*clean_var;

	if (!var || !env)
		return (NULL);
	if (var[0] == '$')
		clean_var = var + 1;
	else
		clean_var = var;
	value = get_env(clean_var, env);
	if (value)
		return (ft_strdup(value));
	return (NULL);
}

int	simplest_cd(char **args, char ***envp)
{
	char	*path;
	char	*new_pwd;

	path = args[1];
	if (ft_strcmp(path, "..") == 0)
	{
		if (getcwd(NULL, 0) == NULL)
			return (handle_cd_dotdot(envp));
	}
	if (access(path, F_OK) != 0)
	{
		perror("cd");
		return (1);
	}
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		*envp = set_env(*envp, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}

int	cd_start(char ***envp)
{
	char	*home;
	char	*new_pwd;

	home = get_var_val("HOME", *envp);
	if (!home)
		return (print_error("cd", "HOME not set"), 1);
	if (chdir(home) != 0)
	{
		free(home);
		return (perror("cd"), 1);
	}
	free(home);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		*envp = set_env(*envp, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}

int	builtin_cd(char **args, char ***envp)
{
	if (args[1] == NULL)
		return (cd_start(envp));
	if (args[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		return (2);
	}
	return (simplest_cd(args, envp));
}
