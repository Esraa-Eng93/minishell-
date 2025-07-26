/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:17 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:18 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	heredoc_child_cleanup(t_cmd *current, t_env *env, int fd)
{
	close(fd);
	free(current->tmp_file);
	clean_all(current, env);
	exit(0);
}

static void	handle_heredoc_input_loop(t_cmd *current, t_env *env,
		char *delimiter, int fd)
{
	char	*line;

	while (current && current->heredoce_count > 0)
	{
		line = readline("> ");
		if (!line)
		{
			print_heredoc_eof_warning(delimiter);
			heredoc_child_cleanup(current, env, fd);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			free(current->tmp_file);
			break ;
		}
		if (env->quote_type == 0)
		{
			expand_variables_in_line(&line, env);
			expand_exitstatus_in_line(&line, env);
		}
		handle_heredoc_line(line, fd);
	}
}

static char	*heredoc_child_process(t_cmd *current, t_env *env,
		char *delimiter)
{
	int	fd;

	signal(SIGINT, heredoc_sigint_handler);
	fd = open_tmp_file(current->tmp_file);
	if (fd == -1)
	{
		free(current->tmp_file);
		exit(1);
	}
	handle_heredoc_input_loop(current, env, delimiter, fd);
	close(fd);
	clean_all(current, env);
	exit(0);
}

static char	*heredoc_parent_process(int pid, t_cmd *current,
		t_env *env, void (*prev_sigint)(int))
{
	int	status;

	waitpid(pid, &status, 0);
	restore_signal(prev_sigint);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		env->shell->exit_status = 130;
		unlink(current->tmp_file);
		free(current->tmp_file);
		return ((char *)HEREDOC_SIGNAL);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		env->shell->exit_status = 1;
		unlink(current->tmp_file);
		free(current->tmp_file);
		return (NULL);
	}
	return (current->tmp_file);
}

char	*get_heredoc_input(char *delimiter, t_cmd *current, t_env *env)
{
	int		pid;
	void	(*prev_sigint)(int);

	current->tmp_file = ft_strdup("/tmp/.heredoc_tmp");
	if (!current->tmp_file)
		return (NULL);
	prev_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		handle_fork_failure(env, current->tmp_file);
		return (NULL);
	}
	if (pid == 0)
		heredoc_child_process(current, env, delimiter);
	return (heredoc_parent_process(pid, current, env, prev_sigint));
}
