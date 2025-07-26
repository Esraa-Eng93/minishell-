/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_analyzing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:21:08 by snazzal           #+#    #+#             */
/*   Updated: 2025/06/03 13:21:15 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static t_cmd	*handle_word(char **tokens, int start, int end, t_cmd *cmd)
{
	int	i;

	i = start;
	cmd = init_cmd();
	cmd->type = COMMAND;
	cmd->args = mem_allocation(sizeof(char *) * (end - start + 2));
	while (i <= end)
	{
		cmd->args[i - start] = ft_strdup(tokens[i]);
		i++;
	}
	cmd->args[end - start + 1] = NULL;
	return (cmd);
}

static t_cmd	*handle_pipe(char **tokens, int start, int end, t_cmd *node)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			node = init_cmd();
			node->type = PIPE;
			node->left = tree_analyzing(tokens, start, i - 1, node);
			node->right = tree_analyzing(tokens, i + 1, end, node);
			return (node);
		}
		i++;
	}
	return (NULL);
}

t_cmd	*tree_analyzing(char **tokens, int start, int end, t_cmd *node)
{
	if (start > end)
		return (NULL);
	node = handle_pipe(tokens, start, end, node);
	if (node)
		return (node);
	node = handle_redirection(tokens, start, end, node);
	if (node)
	{
		node->red_out_cmd = fill_red_out_cmd(tokens, start, end);
		get_last_redirection_filename(tokens, node);
		return (node);
	}
	node = handle_word(tokens, start, end, node);
	return (node);
}

int	prepare_heredocs(t_cmd *node, t_env **env)
{
	if (!node)
		return (SUCCESS);
	if (node->heredoce_count > 0)
	{
		node->fd_heredoc = heredoc_handle(node, *env);
		if (node->fd_heredoc == FAILER)
		{
			g_recived_signals = 0;
			return (FAILER);
		}
	}
	if (prepare_heredocs(node->left, env) == FAILER)
		return (FAILER);
	if (prepare_heredocs(node->right, env) == FAILER)
		return (FAILER);
	return (SUCCESS);
}
