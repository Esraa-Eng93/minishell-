/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:24:58 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:43:31 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	open_append_file(const char *filename, t_env *env)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		env->shell->exit_status = 1;
	}
	return (fd);
}

int	open_append_loop(t_cmd *node, t_env **env,
			int *append_fds, int *fd_append)
{
	int	i;
	int	j;

	i = 0;
	while (i < node->append_file_count)
	{
		append_fds[i] = open_append_file(node->append_file[i], *env);
		if (append_fds[i] == -1)
		{
			j = 0;
			while (j < i)
				close(append_fds[j++]);
			(*env)->shell->exit_status = 1;
			free(append_fds);
			return (FAILER);
		}
		if (i == node->append_file_count - 1)
			*fd_append = append_fds[i];
		else
			close(append_fds[i]);
		i++;
	}
	return (SUCCESS);
}

int	open_append_files(t_cmd *node, t_env **env, int *fd_append)
{
	int	*append_fds;

	append_fds = malloc(sizeof(int) * node->append_file_count);
	if (!append_fds)
		return (FAILER);
	if (open_append_loop(node, env, append_fds, fd_append) == FAILER)
		return (FAILER);
	free(append_fds);
	return (SUCCESS);
}

void	execuation_append(int fd_append, t_cmd *node)
{
	if (fd_append != -1 && node->final_redir_type == APPEND_OUT)
		dup2(fd_append, STDOUT_FILENO);
}
