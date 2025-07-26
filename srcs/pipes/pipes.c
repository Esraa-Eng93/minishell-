/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:00:00 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:59 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	handle_child_left(t_cmd *cmd, t_env **env,
		int input_fd, int pipe_fd[2])
{
	int	exit_status;

	exit_status = 0;
	reset_signals();
	if (dup2(input_fd, STDIN_FILENO) == -1
		|| dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		clean_all(cmd->root, *env);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (execute_tree(cmd->left, env, (*env)->shell) == FAILER)
	{
		exit_status = (*env)->shell->exit_status;
		clean_all(cmd->root, *env);
		exit(exit_status);
	}
	exit_status = (*env)->shell->exit_status;
	clean_all(cmd->root, *env);
	exit(exit_status);
}

int	fork_child_left(t_cmd *cmd, t_env **env,
		int input_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_fork_error(env);
	if (pid == 0)
		handle_child_left(cmd, env, input_fd, pipe_fd);
	if (cmd->left && cmd->left->fd_heredoc != -1)
	{
		close(cmd->left->fd_heredoc);
		cmd->left->fd_heredoc = -1;
	}
	return (pid);
}

static void	handle_child_last(t_cmd *cmd, t_env **env, t_cmd *root,
		int input_fd)
{
	int	exit_status;

	exit_status = 0;
	reset_signals();
	if (cmd && cmd->fd_heredoc != -1)
	{
		dup2(cmd->fd_heredoc, STDIN_FILENO);
		close(cmd->fd_heredoc);
	}
	else if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (execute_tree(cmd, env, (*env)->shell) == FAILER)
	{
		exit_status = (*env)->shell->exit_status;
		clean_all(root, *env);
		exit(exit_status);
	}
	exit_status = (*env)->shell->exit_status;
	clean_all(root, *env);
	exit(exit_status);
}

int	fork_child_last(t_cmd *cmd, t_env **env, t_cmd *root,
		int input_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_fork_error(env);
	if (pid == 0)
		handle_child_last(cmd, env, root, input_fd);
	if (cmd && cmd->fd_heredoc != -1)
	{
		close(cmd->fd_heredoc);
		cmd->fd_heredoc = -1;
	}
	return (pid);
}

void	wait_for_children(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	waited;

	waited = wait(&status);
	while (waited > 0)
	{
		if (waited == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
			else
				shell->exit_status = 1;
		}
		waited = wait(&status);
	}
}
