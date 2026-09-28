/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:15:37 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/18 01:22:41 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_input_redirection(t_cmd *cmd, char *str)
{
	char	*temp;

	str++;
	temp = extract_filename(str);
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = remove_quotes(temp);
	free(temp);
	return (0);
}

int	create_file_if_needed(char *filename, int append)
{
	int	fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(filename, strerror(errno));
		g_exit_status = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

static int	check_single_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(filename, "No such file or directory");
		g_exit_status = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

static int	process_input_redirection(char *str, int *i)
{
	char	*temp;
	char	*filename;
	int		result;

	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		*i += 2;
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
		return (0);
	}
	(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	temp = extract_filename(&str[*i]);
	filename = remove_quotes(temp);
	free(temp);
	result = check_single_input_file(filename);
	free(filename);
	return (result);
}

int	validate_input_files(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
		}
		else if (str[i] == '<')
		{
			if (process_input_redirection(str, &i) == -1)
				return (-1);
			skip_filename_in_string(str, &i);
		}
		else
			i++;
	}
	return (0);
}
