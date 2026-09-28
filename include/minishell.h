/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:56:21 by acerezo-          #+#    #+#             */
/*   Updated: 2025/08/18 16:33:53 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <limits.h>
# include <errno.h>

# define PROMPT "minishell$ "

extern int	g_exit_status;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	char			*delimiter;
	char			**heredoc_delimiters;
	int				heredoc_count;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	t_cmd	*cmds;
}	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Parsing
t_cmd	*parse_input(char *input);
char	**split_pipes(char *input);
t_cmd	*create_cmd(char *cmd_str);
t_cmd	*create_cmd_internal(char *cmd_str, int is_pipeline);
int		parse_redirections(t_cmd *cmd, char *str, int is_pipeline);
char	**parse_args(char *str);
char	**split_args_quotes(char *str);
char	*remove_redirections(char *str);
int		validate_syntax(char *input);
int		check_redirect_syntax(char *input);

// Execute
int		execute_cmds(t_cmd *cmds, t_shell *shell);
int		execute_single(t_cmd *cmd, t_shell *shell);
int		execute_external(t_cmd *cmd, t_shell *shell, char *cmd_name);
void	execute_pipeline(t_cmd *cmds, t_shell *shell);
void	execute_second_child(t_cmd *cmds,
			t_shell *shell, int input_fd);
void	finalize_pipeline(pid_t pid1, pid_t pid2, int *status, t_cmd *cmds);
int		exec_command(t_cmd *cmd, t_shell *shell);
void	preprocess_args(t_cmd *cmd, char **envp);
int		wait_and_get_status(pid_t pid);

// Redirects

int		parse_redirections(t_cmd *cmd, char *str, int is_pipeline);
char	*extract_filename(char *str);
int		create_file_if_needed(char *filename, int append);
int		validate_input_files(char *str);
void	skip_filename_in_string(char *str, int *i);
void	handle_heredoc(t_cmd *cmd, char *str);
int		parse_input_redirection(t_cmd *cmd, char *str);
int		handle_output_append(t_cmd *cmd, char *str, int *i, int is_pipeline);
int		handle_output_trunc(t_cmd *cmd, char *str, int *i, int is_pipeline);
int		handle_heredoc_parse(t_cmd *cmd, char *str, int *i);
int		handle_input_parse(t_cmd *cmd, char *str, int *i, int is_pipeline);
int		setup_input_redirection(t_cmd *cmd, char **envp);
int		setup_output_redirection(t_cmd *cmd);
int		setup_redirections(t_cmd *cmd, char **envp);
int		process_all_heredocs(t_cmd *cmd, char **envp);
int		read_heredoc_to_pipe(char *delimiter, char **envp);
int		manage_heredoc(char *delimiter, char **envp);

// Environment
char	**copy_env(char **envp);
char	*get_env(char *name, char **envp);
char	**elim_env(char **envp, char *key);
char	**set_env(char **envp, char *key, char *value);
char	**increment_shlvl(char **envp);

// Utils
char	*find_path(char *cmd, char **envp);
char	*expand_vars(char *str, char **envp);
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmd *cmds);
void	free_array(char **arr);
void	print_error(char *cmd, char *msg);
void	setup_signals(void);
char	*remove_quotes(char *str);
char	*extract_filename(char *str);
void	check_just_quotes(t_cmd *cmd);

// Expand utils
char	*get_var_name(char *str, int *i);
char	*char_to_str(char c);
char	*process_variable_expansion(char *str, int *i, char **envp);
char	*expand_vars_heredoc(char *str, char **envp);

//builtins
int		is_builtin(char *cmd);
int		run_builtin(char **args, t_shell *shell);
int		has_flag(char *str);
char	*get_pwd(void);
int		builtin_pwd(void);
int		builtin_unset(char *key, t_shell *shell);
int		builtin_echo(char **args, t_shell *shell);
int		builtin_cd(char **args, char ***envp);
int		builtin_exit(char **args, t_shell *shell);
int		builtin_export(char **args, t_shell *shell);
int		builtin_env(char **envp);

// CD utils functions
char	*find_valid_parent(char *current_path);
char	*get_current_path(char **envp);
int		update_pwd_env(char ***envp);
int		handle_cd_dotdot(char ***envp);

// Helper functions for export builtin (shared between files)
int		is_valid_identifier(char *str);
char	*get_export_var_name(char *str);
char	*get_var_value(char *str);
int		find_env_index(char **envp, char *key);

// Helper functions for exit builtin
int		is_numeric(char *str);
long	ft_atol(char *str);

// Signal handling
void	setup_signals(void);
void	setup_signals_executing(void);
void	ignore_signals(void);
void	restore_signals(void);
void	signal_handler(int sig);
void	signal_handler_executing(int sig);

#endif
