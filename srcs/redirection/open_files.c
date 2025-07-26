/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:14 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:15 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	open_input_redirection(t_cmd *node, t_env **env, int *fd_in)
{
	*fd_in = -1;
	if (open_input_files(node, env, fd_in) == FAILER)
		return (FAILER);
	return (SUCCESS);
}

int	open_output_redirection(t_cmd *node, t_env **env, int *fd_out)
{
	*fd_out = -1;
	if (open_output_files(node, env, fd_out) == FAILER)
		return (FAILER);
	return (SUCCESS);
}

int	open_append_redirection(t_cmd *node, t_env **env, int *fd_append)
{
	*fd_append = -1;
	if (open_append_files(node, env, fd_append) == FAILER)
		return (FAILER);
	return (SUCCESS);
}

void	prepare_signals_for_execution(void)
{
	signal(SIGINT, my_handler);
	signal(SIGQUIT, my_handler);
}
