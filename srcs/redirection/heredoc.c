/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:12 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:15:26 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int	g_recived_signals;

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_recived_signals = SIGINT;
	write(1, "\n", 1);
	exit(130);
}

void	execuation_heredoc_in(t_cmd *node)
{
	if (node->heredoce_count > 0 && node->fd_heredoc != -1)
		dup2(node->fd_heredoc, STDIN_FILENO);
}
