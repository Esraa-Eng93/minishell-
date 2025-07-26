/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:19 by ealshorm          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:45 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	execute_child_process(char **args, t_env **env,
		char **exec_env, t_cmd *cmd)
{
	DIR	*dir;

	dir = opendir(args[0]);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": is a directory", 2);
		free_tokens(exec_env);
		free_tokens(args);
		clean_all(cmd, *env);
		exit(126);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(args[0], '/'))
		execute_with_absolute_or_relative_path(env, args, cmd, exec_env);
	else
		execute_with_path(args, env, exec_env, cmd);
	clean_all(cmd, *env);
	exit(EXIT_FAILURE);
}

static void	handle_parent_process(pid_t pid, int *status, t_env **env)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		(*env)->shell->exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		printf("\n");
		(*env)->shell->exit_status = 128 + WTERMSIG(*status);
	}
}

int	external_execution(char **args, t_env **env,
		char **exec_env, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		execute_child_process(args, env, exec_env, cmd);
	else if (pid > 0)
		handle_parent_process(pid, &status, env);
	else
	{
		perror("fork failed");
		(*env)->shell->exit_status = 1;
		return (FAILER);
	}
	(*env)->cmd_pid = pid;
	return ((*env)->shell->exit_status);
}
