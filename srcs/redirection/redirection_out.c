/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:30 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:31 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	open_output_file(const char *filename, t_env *env)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		env->shell->exit_status = 1;
	}
	return (fd);
}

int	handle_output_opening(t_cmd *node, t_env **env,
			int *fd_out, int *output_fds)
{
	int	i;
	int	j;

	i = 0;
	while (i < node->output_file_count)
	{
		output_fds[i] = open_output_file(node->output_file[i], *env);
		if (output_fds[i] == -1)
		{
			j = 0;
			while (j < i)
				close(output_fds[j++]);
			(*env)->shell->exit_status = 1;
			free(output_fds);
			return (FAILER);
		}
		if (i == node->output_file_count - 1)
			*fd_out = output_fds[i];
		else
			close(output_fds[i]);
		i++;
	}
	return (SUCCESS);
}

int	open_output_files(t_cmd *node, t_env **env, int *fd_out)
{
	int	*output_fds;

	output_fds = malloc(sizeof(int) * node->output_file_count);
	if (!output_fds)
		return (FAILER);
	if (handle_output_opening(node, env, fd_out, output_fds) == FAILER)
		return (FAILER);
	free(output_fds);
	return (SUCCESS);
}

void	execuation_out(int fd_out, t_cmd *node)
{
	if (fd_out != -1 && node->final_redir_type == REDIR_OUT)
		dup2(fd_out, STDOUT_FILENO);
}
