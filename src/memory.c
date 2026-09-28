/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calguaci <calguaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:32:20 by acerezo-          #+#    #+#             */
/*   Updated: 2025/06/26 19:53:04 by calguaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->delimiter)
		free(cmd->delimiter);
	if (cmd->heredoc_delimiters)
		free_array(cmd->heredoc_delimiters);
	free(cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
}
