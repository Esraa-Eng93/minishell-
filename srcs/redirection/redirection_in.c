/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:27 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:28 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	open_input_file(const char *filename, t_env *env)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		env->shell->exit_status = 1;
	}
	return (fd);
}

int	handle_input_opening(t_cmd *node, t_env **env,
			int *fd_in, int *input_fds)
{
	int	i;
	int	j;

	i = 0;
	while (i < node->input_file_count)
	{
		input_fds[i] = open_input_file(node->input_file[i], *env);
		if (input_fds[i] == -1)
		{
			j = 0;
			while (j < i)
				close(input_fds[j++]);
			(*env)->shell->exit_status = 1;
			free(input_fds);
			return (FAILER);
		}
		if (i == node->input_file_count - 1)
			*fd_in = input_fds[i];
		else
			close(input_fds[i]);
		i++;
	}
	return (SUCCESS);
}

int	open_input_files(t_cmd *node, t_env **env, int *fd_in)
{
	int	*input_fds;

	input_fds = malloc(sizeof(int) * node->input_file_count);
	if (!input_fds)
		return (FAILER);
	if (handle_input_opening(node, env, fd_in, input_fds) == FAILER)
		return (FAILER);
	free(input_fds);
	return (SUCCESS);
}

void	execuation_in(int fd_in, t_cmd *node)
{
	if (fd_in != -1
		&& !(node->heredoce_count > 0 && node->fd_heredoc != -1))
		dup2(fd_in, STDIN_FILENO);
}
