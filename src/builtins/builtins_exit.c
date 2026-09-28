/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 01:57:50 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/18 01:32:34 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Valida código de salida numérico dentro de rango LONG_MIN/MAX
** Maneja casos extremos de overflow con validación de string exacto
*/
static int	is_valid_exit_code(char *str)
{
	long	num;
	int		len;
	int		offset;

	if (!is_numeric(str))
		return (0);
	len = ft_strlen(str);
	if (str[0] == '+' || str[0] == '-')
		len--;
	if (len > 19)
		return (0);
	num = ft_atol(str);
	if (len == 19)
	{
		if (str[0] == '-' && num == LONG_MIN)
			return (ft_strcmp(str, "-9223372036854775808") == 0);
		if (str[0] != '-' && num == LONG_MAX)
		{
			offset = 0;
			if (str[0] == '+')
				offset = 1;
			return (ft_strcmp(str + offset, "9223372036854775807") == 0);
		}
	}
	return (1);
}

int	pre_exit(char **args)
{
	if (!is_valid_exit_code(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	return (0);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!args[1])
	{
		free_array(shell->envp);
		free_cmds(shell->cmds);
		exit(g_exit_status);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (2);
	}
	if (pre_exit(args))
		return (2);
	exit_code = (unsigned char)ft_atol(args[1]);
	free_array(shell->envp);
	free_cmds(shell->cmds);
	exit(exit_code);
}
