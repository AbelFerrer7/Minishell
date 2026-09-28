/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:33:26 by acerezo-          #+#    #+#             */
/*   Updated: 2025/07/23 02:33:33 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_pipe_start(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '|')
	{
		print_error(NULL, "syntax error near unexpected token `|'");
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

static int	handle_pipe_sequence(char *input, int *i)
{
	(*i)++;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	if (input[*i] == '|')
	{
		(*i)++;
		while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
			(*i)++;
		if (input[*i] == '\0')
		{
			print_error(NULL, "syntax error near unexpected token `|'");
			g_exit_status = 2;
			return (0);
		}
	}
	else if (input[*i] == '\0')
	{
		print_error(NULL, "syntax error near unexpected token `|'");
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

static int	check_pipe_syntax(char *input)
{
	int		i;
	char	quote;

	if (!check_pipe_start(input))
		return (0);
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
			if (!handle_pipe_sequence(input, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	validate_syntax(char *input)
{
	if (!check_pipe_syntax(input))
		return (0);
	if (!check_redirect_syntax(input))
		return (0);
	return (1);
}
