/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:25:00 by calguaci          #+#    #+#             */
/*   Updated: 2025/07/18 18:57:45 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_export_var_name(char *str)
{
	char	*equal_pos;
	int		len;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos)
		len = equal_pos - str;
	else
		len = ft_strlen(str);
	return (ft_substr(str, 0, len));
}

char	*get_var_value(char *str)
{
	char	*equal_pos;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos)
		return (ft_strdup(equal_pos + 1));
	return (NULL);
}

int	find_env_index(char **envp, char *key)
{
	int		i;
	int		key_len;
	char	*equal_pos;

	if (!envp || !key)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (equal_pos && (equal_pos - envp[i]) == key_len
			&& ft_strncmp(envp[i], key, key_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
