/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:52:02 by calguaci          #+#    #+#             */
/*   Updated: 2025/08/13 14:59:45 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status = 0;

static char	**set_basic_env_vars(char **envp)
{
	char	*cwd;

	if (!get_env("PWD", envp))
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			envp = set_env(envp, "PWD", cwd);
			free(cwd);
		}
	}
	if (!get_env("PATH", envp))
		envp = set_env(envp, "PATH", "/bin");
	if (!get_env("_", envp))
		envp = set_env(envp, "_", "./minishell");
	return (envp);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = copy_env(envp);
	shell->envp = increment_shlvl(shell->envp);
	shell->envp = set_basic_env_vars(shell->envp);
	shell->cmds = NULL;
}

/*
** Procesa entrada del usuario: parsing y ejecución completa
** Añade a historial, parsea comandos, ejecuta y libera memoria
** Actualiza exit status global con resultado de ejecución
*/
void	process_input(char *input, t_shell *shell)
{
	if (!input || !*input)
		return ;
	add_history(input);
	shell->cmds = parse_input(input);
	if (shell->cmds)
	{
		g_exit_status = execute_cmds(shell->cmds, shell);
		free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	((void)ac, (void)av, init_shell(&shell, envp));
	while (1)
	{
		setup_signals();
		input = readline(PROMPT);
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		(process_input(input, &shell), free(input));
	}
	free_array(shell.envp);
	rl_clear_history();
	return (g_exit_status);
}
