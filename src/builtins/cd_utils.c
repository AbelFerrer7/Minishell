/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:14:50 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/18 13:41:41 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_parent_dir(char *temp)
{
	char	*last_slash;

	last_slash = ft_strrchr(temp, '/');
	if (!last_slash || last_slash == temp)
	{
		free(temp);
		return (NULL);
	}
	*last_slash = '\0';
	return (temp);
}

char	*find_valid_parent(char *current_path)
{
	char	*parent_path;
	char	*temp;

	if (!current_path || ft_strlen(current_path) <= 1)
		return (ft_strdup("/"));
	temp = ft_strdup(current_path);
	while (temp && ft_strlen(temp) > 1)
	{
		if (access(temp, F_OK) == 0)
		{
			parent_path = ft_strdup(temp);
			free(temp);
			return (parent_path);
		}
		temp = find_parent_dir(temp);
		if (!temp)
			return (ft_strdup("/"));
	}
	free(temp);
	return (ft_strdup("/"));
}

char	*get_current_path(char **envp)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		current_pwd = get_env("PWD", envp);
		if (!current_pwd)
			current_pwd = ft_strdup("/");
		else
			current_pwd = ft_strdup(current_pwd);
	}
	return (current_pwd);
}

int	update_pwd_env(char ***envp)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		*envp = set_env(*envp, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}

int	handle_cd_dotdot(char ***envp)
{
	char	*current_pwd;
	char	*valid_parent;

	current_pwd = get_current_path(*envp);
	valid_parent = find_valid_parent(current_pwd);
	free(current_pwd);
	if (chdir(valid_parent) != 0)
		return (free(valid_parent), perror("cd"), 1);
	free(valid_parent);
	return (update_pwd_env(envp));
}
