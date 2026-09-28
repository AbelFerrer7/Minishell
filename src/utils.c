/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:19:01 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/18 17:36:21 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_absolute_path(char *cmd)
{
	struct stat	file_stat;

	if (stat(cmd, &file_stat) == 0 && !S_ISDIR(file_stat.st_mode)
		&& access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

void	check_just_quotes(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (!cmd->args || !cmd->args[0])
		return ;
	if (cmd->args[0][0] == '\'' || cmd->args[0][0] == '\"')
	{
		while (cmd->args[0][i] == cmd->args[0][0])
			i++;
		if (i == ft_strlen(cmd->args[0]))
		{
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*result;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (check_absolute_path(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env("PATH", envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	if (!result)
		free_array(paths);
	return (result);
}

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
