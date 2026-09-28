/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:50:10 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/06 19:59:12 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_export_vars(char **envp)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
			*equal_pos = '=';
		}
		else
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
}

static int	export_single_var(char ***envp_ptr, char *arg)
{
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	key = get_export_var_name(arg);
	value = get_var_value(arg);
	if (value)
		*envp_ptr = set_env(*envp_ptr, key, value);
	free(key);
	if (value)
		free(value);
	return (0);
}

/*
** Builtin export: sin args muestra variables, con args las exporta
** Valida identificadores y maneja múltiples variables
*/
int	builtin_export(char **args, t_shell *shell)
{
	int	i;
	int	exit_status;

	if (!args[1])
	{
		print_export_vars(shell->envp);
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (export_single_var(&shell->envp, args[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
