/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elim_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:57:40 by calguaci          #+#    #+#             */
/*   Updated: 2025/07/22 20:04:38 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	should_remove_env(char *env_var, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(env_var, key, key_len) == 0)
	{
		if (env_var[key_len] == '=' || env_var[key_len] == '\0')
			return (1);
	}
	return (0);
}

static void	copy_env_vars(char **envp, char **new_env, char *key, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		if (!should_remove_env(envp[i], key))
		{
			new_env[j] = envp[i];
			j++;
		}
		else
			free(envp[i]);
		i++;
	}
	new_env[j] = NULL;
}

char	**elim_env(char **envp, char *key)
{
	char	**new_env;
	int		count;

	if (!envp || !key)
		return (envp);
	count = count_env(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (envp);
	copy_env_vars(envp, new_env, key, count);
	free(envp);
	return (new_env);
}
