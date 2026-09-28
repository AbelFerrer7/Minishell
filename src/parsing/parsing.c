/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:07:15 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/12 21:02:11 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_comment(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '#')
		return (1);
	return (0);
}

/*
** Crea cadena de comandos enlazados para pipelines múltiples
** Cada comando se conecta con el siguiente mediante puntero next
** Maneja memoria liberando toda la cadena si falla algún comando
*/
static t_cmd	*create_pipeline_commands(char **pipe_cmds)
{
	t_cmd	*cmds;
	t_cmd	*current;
	int		i;

	cmds = create_cmd_internal(pipe_cmds[0], 1);
	if (!cmds)
		return (NULL);
	current = cmds;
	i = 1;
	while (pipe_cmds[i])
	{
		current->next = create_cmd_internal(pipe_cmds[i], 1);
		if (!current->next)
		{
			free_cmds(cmds);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	return (cmds);
}

/*
** Convierte entrada de usuario en comandos ejecutables
** Valida sintaxis, separa por pipes y crea estructura de comandos enlazados
** Retorna NULL si hay errores de sintaxis o entrada vacía
*/
t_cmd	*parse_input(char *input)
{
	char	**pipe_cmds;
	t_cmd	*cmds;

	if (is_comment(input))
		return (NULL);
	if (!validate_syntax(input))
		return (NULL);
	pipe_cmds = split_pipes(input);
	if (!pipe_cmds || !pipe_cmds[0])
		return (NULL);
	if (pipe_cmds[1])
		cmds = create_pipeline_commands(pipe_cmds);
	else
		cmds = create_cmd(pipe_cmds[0]);
	free_array(pipe_cmds);
	return (cmds);
}
