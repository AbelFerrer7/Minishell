/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:43:40 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/18 17:14:08 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Configura señales para modo interactivo (prompt)
** SIGINT muestra nueva línea, SIGQUIT se ignora
*/
void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Configura señales para procesos en ejecución
** Ambas señales setean exit status apropiado
*/
void	setup_signals_executing(void)
{
	signal(SIGINT, signal_handler_executing);
	signal(SIGQUIT, signal_handler_executing);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler_executing(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit                       (core dumped)\n",
			STDOUT_FILENO);
	}
}
