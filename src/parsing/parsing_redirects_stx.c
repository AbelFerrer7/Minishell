/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirects_stx.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:34:00 by acerezo-          #+#    #+#             */
/*   Updated: 2025/07/23 02:46:16 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_redirect_error(char c, int is_double)
{
	if (c == '\0')
		print_error(NULL, "syntax error near unexpected token `newline'");
	else if (c == '>' && is_double)
		print_error(NULL, "syntax error near unexpected token `>>'");
	else if (c == '>')
		print_error(NULL, "syntax error near unexpected token `>'");
	else if (c == '<' && is_double)
		print_error(NULL, "syntax error near unexpected token `<<'");
	else if (c == '<')
		print_error(NULL, "syntax error near unexpected token `<'");
	else if (c == '|')
		print_error(NULL, "syntax error near unexpected token `|'");
	g_exit_status = 2;
}

static int	check_triple_redirect(char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
	{
		print_error(NULL, "syntax error near unexpected token `>'");
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

static int	validate_redirect_token(char *input, int *i)
{
	int	is_double;

	if (!check_triple_redirect(input, *i))
		return (0);
	is_double = (input[*i] == input[*i + 1]);
	if (is_double)
		(*i)++;
	(*i)++;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	if (input[*i] == '\0' || input[*i] == '>' || input[*i] == '<'
		|| input[*i] == '|')
	{
		print_redirect_error(input[*i],
			is_double && input[*i] == input[*i - 1]);
		return (0);
	}
	return (1);
}

int	check_redirect_syntax(char *input)
{
	int		i;
	char	quote;

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
		else if (input[i] == '>' || input[i] == '<')
		{
			if (!validate_redirect_token(input, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}
