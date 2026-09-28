/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:06:53 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/12 21:11:34 by acerezo-         ###   ########.fr       */
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

char	**copy_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

char	*get_env(char *name, char **envp)
{
	int		i;
	int		len;
	char	*equal;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal && (equal - envp[i]) == len
			&& ft_strncmp(envp[i], name, len) == 0)
			return (equal + 1);
		i++;
	}
	return (NULL);
}

/*
** Establece variable de entorno, reemplazando si existe
** Elimina variable anterior y crea nuevo array con espacio adicional
*/
char	**set_env(char **envp, char *key, char *value)
{
	char	**new_env;
	char	*env_var;
	char	*temp;
	int		count;
	int		i;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (envp);
	env_var = ft_strjoin(temp, value);
	free(temp);
	if (!env_var)
		return (envp);
	envp = elim_env(envp, key);
	count = count_env(envp);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (free(env_var), envp);
	i = -1;
	while (++i < count)
		new_env[i] = envp[i];
	free(envp);
	new_env[count] = env_var;
	new_env[count + 1] = NULL;
	return (new_env);
}

char	**increment_shlvl(char **envp)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env("SHLVL", envp);
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0 || shlvl >= 1000)
			shlvl = 1;
		else
			shlvl++;
	}
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return (envp);
	envp = set_env(envp, "SHLVL", new_shlvl);
	free(new_shlvl);
	return (envp);
}
