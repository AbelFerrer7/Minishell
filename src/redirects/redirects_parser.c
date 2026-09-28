/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:43:38 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/13 03:53:25 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	skip_quotes_in_parsing(char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
}

static int	process_redir_type(t_cmd *cmd, char *str, int *i, int pipeline)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		handle_heredoc_parse(cmd, str, i);
		skip_filename_in_string(str, i);
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		if (handle_output_append(cmd, str, i, pipeline) == -1)
			return (-1);
		skip_filename_in_string(str, i);
	}
	else if (str[*i] == '>')
	{
		if (handle_output_trunc(cmd, str, i, pipeline) == -1)
			return (-1);
		skip_filename_in_string(str, i);
	}
	else if (str[*i] == '<')
	{
		if (handle_input_parse(cmd, str, i, pipeline) == -1)
			return (-1);
		skip_filename_in_string(str, i);
	}
	return (0);
}

/*
** Parsea todas las redirecciones (<, >, >>, <<) en un comando
** Valida archivos de entrada y procesa cada tipo de redirección
** Maneja comillas correctamente para evitar parsing erróneo
*/
int	parse_redirections(t_cmd *cmd, char *str, int is_pipeline)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			skip_quotes_in_parsing(str, &i);
		else if (str[i] == '<' || str[i] == '>')
		{
			if (process_redir_type(cmd, str, &i, is_pipeline) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
