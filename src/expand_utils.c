/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:41:41 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/18 17:37:34 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_name(char *str, int *i)
{
	int		start;
	char	*name;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	return (name);
}

/*
** Procesa la expansión de una variable específica ($?, $VAR, $)
** Maneja casos especiales como $? para exit status
*/
char	*process_variable_expansion(char *str, int *i, char **envp)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (str[*i] == '?')
	{
		var_value = ft_itoa(g_exit_status);
		(*i)++;
	}
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		var_name = get_var_name(str, i);
		var_value = get_env(var_name, envp);
		if (!var_value)
			var_value = ft_strdup("");
		else
			var_value = ft_strdup(var_value);
		free(var_name);
	}
	else
	{
		var_value = ft_strdup("$");
	}
	return (var_value);
}

static char	*process_dollar(char *str, int *i, char **envp, char *result)
{
	char	*var_value;
	char	*temp;

	var_value = process_variable_expansion(str, i, envp);
	temp = ft_strjoin(result, var_value);
	free(result);
	free(var_value);
	return (temp);
}

static char	*process_regular_char(char *str, int *i, char *result)
{
	char	*temp;
	char	*new_result;

	temp = char_to_str(str[(*i)++]);
	new_result = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (new_result);
}

char	*expand_vars_heredoc(char *str, char **envp)
{
	char	*result;
	int		i;

	if (!str || !ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			result = process_dollar(str, &i, envp, result);
		else
			result = process_regular_char(str, &i, result);
	}
	return (result);
}
