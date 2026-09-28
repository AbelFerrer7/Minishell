/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:35:02 by calguaci          #+#    #+#             */
/*   Updated: 2025/07/22 19:50:08 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*append_char_to_result(char *result, char c)
{
	char	*temp;
	char	*var_value;

	temp = char_to_str(c);
	var_value = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (var_value);
}

static char	*process_single_quotes(char *str, int *i, char *result)
{
	result = append_char_to_result(result, str[*i]);
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		result = append_char_to_result(result, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
	{
		result = append_char_to_result(result, str[*i]);
		(*i)++;
	}
	return (result);
}

static char	*process_regular_character(char *str, int *i, char *result)
{
	char	*temp;
	char	*var_value;

	if (str[*i] == '$')
	{
		var_value = ft_strdup("$");
		temp = ft_strjoin(result, var_value);
		free(result);
		free(var_value);
		result = temp;
		(*i)++;
	}
	else
	{
		temp = char_to_str(str[*i]);
		var_value = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = var_value;
		(*i)++;
	}
	return (result);
}

/*
** Expande variables de entorno ($VAR, $?) respetando comillas simples
** Las comillas simples bloquean expansión, dobles la permiten
*/
char	*expand_vars(char *str, char **envp)
{
	char	*result;
	char	*var_value;
	char	*temp;
	int		i;

	if (!str || !ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = process_single_quotes(str, &i, result);
		else if (str[i] == '$' && str[i + 1])
		{
			var_value = process_variable_expansion(str, &i, envp);
			temp = ft_strjoin(result, var_value);
			free(result);
			free(var_value);
			result = temp;
		}
		else
			result = process_regular_character(str, &i, result);
	}
	return (result);
}
