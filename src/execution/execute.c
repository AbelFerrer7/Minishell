/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:41:41 by acerezo-          #+#    #+#             */
/*   Updated: 2025/07/22 19:29:01 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Procesa argumentos expandiendo variables y eliminando comillas
** Maneja memoria liberando strings temporales correctamente
*/
void	preprocess_args(t_cmd *cmd, char **envp)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmd->args[i])
	{
		temp = cmd->args[i];
		cmd->args[i] = expand_vars(cmd->args[i], envp);
		free(temp);
		temp = cmd->args[i];
		cmd->args[i] = remove_quotes(cmd->args[i]);
		if (cmd->args[i])
			free(temp);
		else
			cmd->args[i] = temp;
		i++;
	}
}
