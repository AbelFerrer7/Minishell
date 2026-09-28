/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:31:58 by acerezo-          #+#    #+#             */
/*   Updated: 2025/07/23 02:53:47 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_pipes(char *input)
{
	int		count;
	int		i;
	char	quote;

	count = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i])
				i++;
		}
		else if (input[i] == '|')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static void	skip_pipes_quotes(char *input, int *i)
{
	char	quote;

	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i])
		(*i)++;
}

static void	extract_pipe_segments(char *input, char **result, int count)
{
	char	*start;
	int		i;
	int		segment;

	start = input;
	i = 0;
	segment = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			skip_pipes_quotes(input, &i);
		else if (input[i] == '|')
		{
			result[segment++] = ft_substr(start, 0, &input[i] - start);
			start = &input[i + 1];
			i++;
		}
		else
			i++;
	}
	result[segment] = ft_strdup(start);
	result[count] = NULL;
}

/*
** Divide un string por pipes ignorando los que están entre comillas
*/
char	**split_pipes(char *input)
{
	char	**result;
	int		count;

	count = count_pipes(input);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	extract_pipe_segments(input, result, count);
	return (result);
}
