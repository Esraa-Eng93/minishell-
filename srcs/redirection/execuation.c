/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:08:59 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:59:10 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	close_all_fds(int fd_in, int fd_out, int fd_append, int fd_heredoc)
{
	if (fd_heredoc != -1)
		close(fd_heredoc);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	if (fd_append != -1)
		close(fd_append);
}

void	run_child_execution(t_cmd *node, t_env **env,
			int fds[3])
{
	int	exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execuation_heredoc_in(node);
	execuation_in(fds[0], node);
	execuation_out(fds[1], node);
	execuation_append(fds[2], node);
	close_all_fds(fds[0], fds[1], fds[2], node->fd_heredoc);
	if (node->red_out_cmd && node->red_out_cmd[0])
		minishell_execuation(node->red_out_cmd, env, node);
	exit_status = (*env)->shell->exit_status;
	clean_all(node, *env);
	exit(exit_status);
}

void	run_parent_handling(t_cmd *node, t_env **env,
			int pid, int fd_heredoc)
{
	int	status;

	(void)fd_heredoc;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*env)->shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->shell->exit_status = 128 + WTERMSIG(status);
	if (node->left && node->left->args
		&& ft_strcmp(node->left->args[0], "exit") == 0)
		exit((*env)->shell->exit_status);
}

int	execute_with_redirection_in_out(t_cmd *node, t_env **env)
{
	int		fds[3];
	pid_t	pid;

	fds[0] = -1;
	fds[1] = -1;
	fds[2] = -1;
	prepare_signals_for_execution();
	if (open_input_redirection(node, env, &fds[0]) == FAILER)
		return (FAILER);
	if (open_output_redirection(node, env, &fds[1]) == FAILER)
		return (FAILER);
	if (open_append_redirection(node, env, &fds[2]) == FAILER)
		return (FAILER);
	pid = fork();
	if (pid == 0)
		run_child_execution(node, env, fds);
	else
	{
		run_parent_handling(node, env, pid, node->fd_heredoc);
		close_all_fds(fds[0], fds[1], fds[2], node->fd_heredoc);
	}
	return (SUCCESS);
}

int	execute_with_redirection(t_cmd *node, t_env **env, t_shell *shell)
{
	int	status;

	(void)shell;
	status = SUCCESS;
	if (node->heredoce_count > 0 || node->input_file_count > 0
		|| node->output_file_count > 0 || node->append_file_count > 0)
	{
		if (execute_with_redirection_in_out(node, env) == FAILER)
			status = FAILER;
	}
	return (status);
}
