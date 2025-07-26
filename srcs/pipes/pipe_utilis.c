/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:00:00 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:44 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	handle_fork_error(t_env **env)
{
	perror("fork");
	(*env)->shell->exit_status = 1;
	return (FAILER);
}

int	create_pipe(int pipe_fd[2], t_shell *shell)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		shell->exit_status = 1;
		return (FAILER);
	}
	return (SUCCESS);
}
