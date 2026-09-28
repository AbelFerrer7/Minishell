/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:32:49 by acerezo-          #+#    #+#             */
/*   Updated: 2025/07/23 02:55:14 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	skip_quotes_in_args(char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
}

static int	count_args(char *str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
			{
				if (str[i] == '\'' || str[i] == '\"')
					skip_quotes_in_args(str, &i);
				else
					i++;
			}
		}
	}
	return (count);
}

static char	*get_next_arg(char *str, int *i)
{
	int		start;
	char	quote;

	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quote = str[(*i)++];
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

/*
** Divide un string en argumentos respetando las comillas
*/
char	**split_args_quotes(char *str)
{
	char	**args;
	int		count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	count = count_args(str);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		args[j] = get_next_arg(str, &i);
		if (!args[j])
		{
			free_array(args);
			return (NULL);
		}
		j++;
	}
	args[j] = NULL;
	return (args);
}

char	**parse_args(char *str)
{
	char	**args;
	char	*clean_str;

	clean_str = remove_redirections(str);
	if (!clean_str)
		return (NULL);
	args = split_args_quotes(clean_str);
	free(clean_str);
	return (args);
}
