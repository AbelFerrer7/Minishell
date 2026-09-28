/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:33:09 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/06 18:47:31 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	copy_quoted_content(char *str, int *i, char *clean_str, int *j)
{
	char	quote;

	quote = str[*i];
	clean_str[(*j)++] = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		clean_str[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
		clean_str[(*j)++] = str[(*i)++];
}

static void	skip_filename_section(char *str, int *i)
{
	char	quote;

	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quote = str[(*i)++];
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
}

static void	process_redirection(char *str, int *i, int *j, char *clean_str)
{
	int	need_space;

	need_space = 0;
	if (*j > 0 && clean_str[*j - 1] != ' ' && clean_str[*j - 1] != '\t')
		need_space = 1;
	if (str[*i] == str[*i + 1])
		(*i)++;
	(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	skip_filename_section(str, i);
	if (need_space && str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '<' && str[*i] != '>')
		clean_str[(*j)++] = ' ';
}

/*
** Elimina las redirecciones de un string conservando las comillas
** Solo añade espacio si es necesario para separar argumentos
*/
char	*remove_redirections(char *str)
{
	char	*clean_str;
	int		i;
	int		j;

	clean_str = malloc(ft_strlen(str) + 1);
	if (!clean_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			copy_quoted_content(str, &i, clean_str, &j);
		else if (str[i] == '<' || str[i] == '>')
			process_redirection(str, &i, &j, clean_str);
		else
			clean_str[j++] = str[i++];
	}
	clean_str[j] = '\0';
	return (clean_str);
}
