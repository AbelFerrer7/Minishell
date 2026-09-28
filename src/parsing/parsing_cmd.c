/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:32:23 by acerezo-          #+#    #+#             */
/*   Updated: 2025/07/23 02:32:24 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->delimiter = NULL;
	cmd->heredoc_delimiters = NULL;
	cmd->heredoc_count = 0;
	cmd->next = NULL;
	return (cmd);
}

/*
** Crea estructura t_cmd desde string de comando individual
** Parsea redirecciones y argumentos, manejando pipelines y comandos únicos
** Libera memoria automáticamente si falla cualquier paso del parsing
*/
t_cmd	*create_cmd_internal(char *cmd_str, int is_pipeline)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	if (parse_redirections(cmd, cmd_str, is_pipeline) == -1)
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->args = parse_args(cmd_str);
	if (!cmd->args)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*create_cmd(char *cmd_str)
{
	return (create_cmd_internal(cmd_str, 0));
}
