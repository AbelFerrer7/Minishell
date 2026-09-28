/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_extract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:48:30 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/18 16:33:44 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static char	*extract_quoted_filename(char *end, char quote)
{
	end++;
	while (*end && *end != quote)
		end++;
	if (*end == quote)
		end++;
	return (end);
}

char	*extract_filename(char *str)
{
	char	*start;
	char	*end;
	char	quote;
	int		len;

	start = skip_spaces(str);
	end = start;
	while (*end && *end != ' ' && *end != '\t' && *end != '<' && *end != '>')
	{
		if (*end == '\'' || *end == '\"')
		{
			quote = *end;
			end = extract_quoted_filename(end, quote);
		}
		else
			end++;
	}
	len = end - start;
	return (ft_substr(start, 0, len));
}

static char	**realloc_delimiters(char **old_arr, int old_size)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (old_size + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_arr[i] = old_arr[i];
		i++;
	}
	new_arr[i] = NULL;
	new_arr[i + 1] = NULL;
	if (old_arr)
		free(old_arr);
	return (new_arr);
}

void	handle_heredoc(t_cmd *cmd, char *str)
{
	char	*temp;
	char	*delimiter;

	cmd->heredoc = 1;
	str += 2;
	temp = extract_filename(str);
	delimiter = remove_quotes(temp);
	free(temp);
	cmd->heredoc_delimiters = realloc_delimiters(cmd->heredoc_delimiters,
			cmd->heredoc_count);
	if (!cmd->heredoc_delimiters)
	{
		free(delimiter);
		cmd->heredoc = 0;
		cmd->heredoc_count = 0;
		return ;
	}
	cmd->heredoc_delimiters[cmd->heredoc_count] = delimiter;
	cmd->heredoc_count++;
	if (cmd->delimiter)
		free(cmd->delimiter);
	cmd->delimiter = ft_strdup(delimiter);
}
