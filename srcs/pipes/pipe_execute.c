/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:00:00 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:41 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	execute_pipeline_loop(t_cmd *cmd, t_env **env,
		int *input_fd, t_shell *shell)
{
	int		pipe_fd[2];
	t_cmd	*current;

	current = cmd;
	while (current && current->type == PIPE)
	{
		if (create_pipe(pipe_fd, shell) == FAILER)
		{
			clean_all(cmd, *env);
			return (FAILER);
		}
		if (fork_child_left(current, env, *input_fd, pipe_fd) == FAILER)
			return (FAILER);
		close(pipe_fd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = pipe_fd[0];
		current = current->right;
	}
	return (SUCCESS);
}

int	execute_pipeline(t_cmd *cmd, t_env **env, t_shell *shell)
{
	int		input_fd;
	t_cmd	*current;
	pid_t	last_pid;

	input_fd = STDIN_FILENO;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cmd->root = cmd;
	if (cmd->fd_heredoc != -1)
		input_fd = cmd->fd_heredoc;
	else if (cmd->left && cmd->left->fd_heredoc != -1)
		input_fd = cmd->left->fd_heredoc;
	current = cmd;
	if (execute_pipeline_loop(cmd, env, &input_fd, shell) == FAILER)
		return (FAILER);
	while (current && current->type == PIPE)
		current = current->right;
	last_pid = fork_child_last(current, env, cmd, input_fd);
	if (last_pid == FAILER)
		return (FAILER);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	wait_for_children(last_pid, shell);
	return (SUCCESS);
}
