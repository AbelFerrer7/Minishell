/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:38:21 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/13 05:05:18 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_filename_in_string(char *str, int *i)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i] == quote)
			(*i)++;
	}
	else
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
			&& str[*i] != '<' && str[*i] != '>')
			(*i)++;
	}
}

/*
** Maneja redirección de append (>>), creando archivo si no existe
** Libera outfile anterior para evitar memory leaks
*/
int	handle_output_append(t_cmd *cmd, char *str, int *i, int is_pipeline)
{
	char	*temp;
	char	*filename;
	int		create_result;

	(void)is_pipeline;
	*i += 2;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	temp = extract_filename(&str[*i]);
	filename = remove_quotes(temp);
	create_result = create_file_if_needed(filename, 1);
	if (create_result == -1 && !is_pipeline)
	{
		free(filename);
		free(temp);
		return (-1);
	}
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = filename;
	cmd->append = 1;
	free(temp);
	return (0);
}

int	handle_output_trunc(t_cmd *cmd, char *str, int *i, int is_pipeline)
{
	char	*temp;
	char	*filename;
	int		create_result;

	(void)is_pipeline;
	(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	temp = extract_filename(&str[*i]);
	filename = remove_quotes(temp);
	create_result = create_file_if_needed(filename, 0);
	if (create_result == -1 && !is_pipeline)
		return (free(filename), free(temp), -1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = filename;
	cmd->append = 0;
	free(temp);
	return (0);
}

int	handle_heredoc_parse(t_cmd *cmd, char *str, int *i)
{
	char	*pos;

	pos = &str[*i];
	handle_heredoc(cmd, pos);
	*i += 2;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	return (0);
}

int	handle_input_parse(t_cmd *cmd, char *str, int *i, int is_pipeline)
{
	char	*pos;
	char	*temp;
	char	*filename;
	int		fd;

	pos = &str[*i];
	if (parse_input_redirection(cmd, pos) == -1)
		return (-1);
	(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!is_pipeline)
	{
		temp = extract_filename(&str[*i]);
		filename = remove_quotes(temp);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			print_error(filename, "No such file or directory");
			g_exit_status = 1;
			return (free(filename), free(temp), -1);
		}
		(close(fd), free(filename), free(temp));
	}
	return (0);
}
