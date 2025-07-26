/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:24 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:25 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	init_heredoc_file(t_cmd *node)
{
	int	k;

	node->heredoc_file = malloc(sizeof(char *) * (node->heredoce_count + 1));
	if (!node->heredoc_file)
		return (FAILER);
	k = 0;
	while (k <= node->heredoce_count)
		node->heredoc_file[k++] = NULL;
	return (0);
}

static void	cleanup_heredoc_files(t_cmd *node, int *heredoc_fds, int limit)
{
	int	j;

	j = 0;
	while (j < limit)
	{
		if (heredoc_fds[j] != -1)
			close(heredoc_fds[j]);
		if (node->heredoc_file[j])
			unlink(node->heredoc_file[j]);
		j++;
	}
	free(node->heredoc_file);
	node->heredoc_file = NULL;
}

static int	handle_heredoc_input(t_cmd *node, t_env *env,
				int *heredoc_fds, int i)
{
	node->heredoc_file[i] = get_heredoc_input(
			node->heredoc_delimiter[i], node, env);
	if (!node->heredoc_file[i]
		|| node->heredoc_file[i] == (char *)HEREDOC_SIGNAL)
	{
		cleanup_heredoc_files(node, heredoc_fds, i);
		return (FAILER);
	}
	return (0);
}

static int	handle_open_file(t_cmd *node, t_env *env,
				int *heredoc_fds, int i)
{
	heredoc_fds[i] = open_input_file(node->heredoc_file[i], env);
	if (heredoc_fds[i] == -1)
	{
		cleanup_heredoc_files(node, heredoc_fds, i + 1);
		env->shell->exit_status = 1;
		return (FAILER);
	}
	return (0);
}

int	heredoc_handle(t_cmd *node, t_env *env)
{
	int	fd;
	int	i;
	int	heredoc_fds[1024];

	fd = -1;
	i = 0;
	if (init_heredoc_file(node) == FAILER)
		return (FAILER);
	while (i < node->heredoce_count)
	{
		if (handle_heredoc_input(node, env, heredoc_fds, i) == FAILER)
			return (FAILER);
		if (handle_open_file(node, env, heredoc_fds, i) == FAILER)
			return (FAILER);
		if (i == node->heredoce_count - 1)
			fd = heredoc_fds[i];
		else
			close(heredoc_fds[i]);
		i++;
	}
	node->heredoc_file[node->heredoce_count] = NULL;
	return (fd);
}
