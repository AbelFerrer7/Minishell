/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:41:07 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/06 19:46:50 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	copy_without_quotes(const char *str, char *result, int len)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (i < len && str[i] != quote)
				result[j++] = str[i++];
			if (i < len)
				i++;
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	copy_without_quotes(str, result, len);
	return (result);
}
