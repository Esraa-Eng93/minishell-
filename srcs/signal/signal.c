/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:08:51 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:08:52 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	g_recived_signals = 0;

void	sigint_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		g_recived_signals = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(t_shell *shell)
{
	struct sigaction	sa;

	(void)shell;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sigint_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
}

void	my_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}
