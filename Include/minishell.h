/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:19:52 by ealshorm          #+#    #+#             */
/*   Updated: 2025/06/03 14:25:04 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

# define PROMPT "minishell:~$  "
# define FAILER 1
# define SUCCESS 0
# define NOT_BUILTIN -1
# define EXIT_CALLED 4242
# define HEREDOC_SIGNAL 130
# define SYNTAX_ERROR -1

extern int			g_recived_signals;

typedef enum e_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_OUT,
	HEREDOC,
	COMMAND
}					t_type;

typedef struct s_shell
{
	int				exit_status;
}					t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	char			quote_type;
	t_shell			*shell;
	pid_t			cmd_pid;
}					t_env;

typedef struct s_cmd
{
	t_type			type;
	char			**args;
	char			**input_file;
	char			**output_file;
	char			**append_file;
	char			**heredoc_file;
	char			**heredoc_delimiter;
	struct s_cmd	*left;
	struct s_cmd	*right;
	int				input_file_count;
	int				output_file_count;
	int				append_file_count;
	char			**red_out_cmd;
	char			*final_redirection;
	t_type			final_redir_type;
	int				heredoce_count;
	int				fd_heredoc;
	char			*tmp_file;
	int				input_fd;
	t_env			*env;
	struct s_cmd	*root;
}					t_cmd;

/* analyzing */
t_cmd				*tree_analyzing(char **tokens, int start, int end,
						t_cmd *node);
char				**split_line_command(const char *input, t_env *env);
int					ft_isspace(char c);
void				free_tokens(char **tokens);
void				*mem_allocation(size_t bytes);
void				free_cmd_tree(t_cmd *cmd);
int					count_words(char **str);
char				*analyzing_pipes_redirections(const char *input, int *i);
t_cmd				*init_cmd(void);
int					check_unclosed_quotes(const char *input, t_shell *shell);
t_cmd				*handle_redirection(char **tokens, int start, int end,
						t_cmd *node);
int					syntax_logic(char **tokens, int start, int end);
char				**expand_and_split_args(char **args, t_env *env);

/* builtins */
t_env				*init_env(t_shell *shell);
void				ft_echo_builtin(char **args);
int					handle_env(t_env *env, char **args);
int					handle_export(t_env **env, char **args);
void				print_env(t_env *env_list);
int					handle_export_with_equal(t_env **env, char *arg,
						int *error_flag);
void				free_env_list(t_env *env_list);
int					handle_cd(char **args, t_env **env);
int					ft_pwd_builtin(char **args, t_shell *shell);
void				my_exit(char **args, t_env **env, t_cmd *cmd);
t_env				*create_env_list(char **env_variables, t_shell *shell);
void				ft_unset(t_env **env, char **args);
int					is_valid_identifier(const char *str);
t_env				*sort_export_list(t_env *env_list);
char				*remove_quotes(const char *str);

/* expand */
char				*get_env_value(t_env *env, char *key);
void				set_env_value(t_env **env, char *key, char *value,
						t_shell *shell);
char				*replace_env_variable(const char *input, t_env *env);
char				*qoute_handle(char *input);

/* execution */
int					minishell_execuation(char **args, t_env **env, t_cmd *cmd);
char				*get_executable_path(char *cmd, t_env *env,
						char *path_value);
char				*join_path(char *dir, char *cmd);
void				increase_shlvl(t_env **env, char **args);
char				**create_env_array(t_env *env);
void				free_exec_env(char **exec_env);
int					execute_tree(t_cmd *node, t_env **env, t_shell *shell);
int					syntax_path(char **args, t_env **env);
int					execute_with_absolute_or_relative_path(t_env **env,
						char **args, t_cmd *cmd, char **new_env2);
int					execute_builtin(char **args, t_env **env, t_cmd *cmd);
int					execute_with_path(char **args, t_env **env, char **exec_env,
						t_cmd *cmd);
int					external_execution(char **args, t_env **env,
						char **exec_env, t_cmd *cmd);

/* signals */
void				setup_signals(t_shell *shell);
void				my_handler(int signum);

/* pipes */
int					execute_pipeline(t_cmd *cmd, t_env **env, t_shell *shell);
void				reset_signals(void);
int					handle_fork_error(t_env **env);
int					create_pipe(int pipe_fd[2], t_shell *shell);
void				wait_for_children(pid_t last_pid, t_shell *shell);
int					fork_child_last(t_cmd *cmd, t_env **env, t_cmd *root,
						int input_fd);
int					fork_child_left(t_cmd *cmd, t_env **env, int input_fd,
						int pipe_fd[2]);

/* redirection */
int					execute_with_redirection_in(t_cmd *node, t_env **env);
int					execute_with_redirection_out(t_cmd *node, t_env **env);
int					execute_with_redirection(t_cmd *node, t_env **env,
						t_shell *shell);
int					execute_with_append_redirection(t_cmd *node, t_env **env,
						t_shell *shell);
int					execute_with_redirection(t_cmd *node, t_env **env,
						t_shell *shell);

int					execute_heredoc(t_cmd *cmd, t_env **env);
int					is_quoted(char *delimiter);
char				*strip_quotes(char *delimiter);
void				expand_variables_in_line(char **line, t_env *env);
void				expand_exitstatus_in_line(char **line, t_env *env);
char				*get_heredoc_input(char *delimiter, t_cmd *current,
						t_env *env);
void				print_cmd_tree(t_cmd *node, int level);
void				print_tokens_tree(char **tokens);
int					count_total_output_redirs(t_cmd *node);
int					count_total_append_redirs(t_cmd *node);
char				**fill_red_out_cmd(char **tokens, int start, int end);
void				get_last_redirection_filename(char **tokens, t_cmd *node);
int					prepare_heredocs(t_cmd *node, t_env **env);
void				clean_all(t_cmd *cmd, t_env *env_list);
void				execuation_heredoc_in(t_cmd *node);
void				execuation_in(int fd_in, t_cmd *node);
void				execuation_out(int fd_out, t_cmd *node);
void				execuation_append(int fd_append, t_cmd *node);
void				prepare_signals_for_execution(void);
void				heredoc_sigint_handler(int signo);

/* open files*/
int					open_output_file(const char *filename, t_env *env);
int					open_append_file(const char *filename, t_env *env);
int					open_append_files(t_cmd *node, t_env **env, int *fd_append);
int					open_output_files(t_cmd *node, t_env **env, int *fd_out);
int					open_input_files(t_cmd *node, t_env **env, int *fd_in);
int					open_input_file(const char *filename, t_env *env);
int					open_input_redirection(t_cmd *node, t_env **env,
						int *fd_in);
int					open_output_redirection(t_cmd *node, t_env **env,
						int *fd_out);
int					open_append_redirection(t_cmd *node, t_env **env,
						int *fd_append);
int					heredoc_handle(t_cmd *node, t_env *env);
void				restore_signal(void (*prev_sigint)(int));
void				handle_fork_failure(t_env *env, char *tmp_file);
int					open_tmp_file(char *tmp_file);
void				print_heredoc_eof_warning(char *delimiter);
void				handle_heredoc_line(char *line, int fd);

char				*check_empty_token(char *token, const char *input, int *i,
						t_env *env);

int					is_redirection(char *token);
char				**tokenize_input(const char *input, int token_count,
						t_env *env);
void				skip_whitespace(const char *input, int *i);
char				*handle_pipes_and_redirects(const char *input, int *i);
char				*export_assignment(const char *input, int *i,
						int *export_mode);
char				*process_normal_token(const char *input, int *i,
						t_env *env);
char				*handle_export_case(const char *input, int *i,
						int *export_mode);
char				*get_token_part(const char *input, int *i, t_env *env);
char				*handle_quotes_if_needed(const char *input, int *i,
						t_env *env, int *disable_env);
char				*handle_quoted_token(const char *input, int *i,
						int *disable_env, t_env *env);
void				add_input_file(t_cmd *cmd, const char *filename);
void				add_append_file(t_cmd *cmd, const char *filename);
void				add_output_file(t_cmd *cmd, const char *filename);
void				add_heredoc_delimiter(t_cmd *node, const char *delimiter);
char				*error_message(int index);
int					is_valid_filename(char *filename);
int					pipe_logic(char **tokens, int start, int end);

#endif
