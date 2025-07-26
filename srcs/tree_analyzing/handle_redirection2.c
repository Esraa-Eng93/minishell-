/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:16:46 by snazzal           #+#    #+#             */
/*   Updated: 2025/06/03 14:28:55 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_cmd	*init_redir_node(t_cmd *curr_node, char **tokens, int start, int i)
{
	t_cmd	*redir_node;

	redir_node = init_cmd();
	if (curr_node)
		redir_node->left = curr_node;
	else
		redir_node->left = tree_analyzing(tokens, start, i - 1, NULL);
	return (redir_node);
}

int	handle_input_redirections(t_cmd *redir_node, char **tokens, int i, int end)
{
	if (ft_strcmp(tokens[i], "<<") == 0 && i + 1 <= end)
	{
		redir_node->type = HEREDOC;
		add_heredoc_delimiter(redir_node, tokens[i + 1]);
		return (2);
	}
	else if (ft_strcmp(tokens[i], "<") == 0 && i + 1 <= end
		&& is_valid_filename(tokens[i + 1]))
	{
		redir_node->type = REDIR_IN;
		add_input_file(redir_node, tokens[i + 1]);
		return (2);
	}
	return (0);
}

int	handle_output_redirections(t_cmd *redir_node, char **tokens, int i, int end)
{
	if (ft_strcmp(tokens[i], ">") == 0 && i + 1 <= end
		&& is_valid_filename(tokens[i + 1]))
	{
		redir_node->type = REDIR_OUT;
		add_output_file(redir_node, tokens[i + 1]);
		return (2);
	}
	else if (ft_strcmp(tokens[i], ">>") == 0 && i + 1 <= end
		&& is_valid_filename(tokens[i + 1]))
	{
		redir_node->type = APPEND_OUT;
		add_append_file(redir_node, tokens[i + 1]);
		return (2);
	}
	return (0);
}

int	process_single_redirection(t_cmd *redir_node, char **tokens, int i, int end)
{
	int	res;

	res = handle_input_redirections(redir_node, tokens, i, end);
	if (res)
		return (res);
	res = handle_output_redirections(redir_node, tokens, i, end);
	if (res)
		return (res);
	return (1);
}

t_cmd	*handle_redirection(char **tokens, int start, int end, t_cmd *node)
{
	int		i;
	t_cmd	*redir_node;
	t_cmd	*curr_node;

	i = start;
	redir_node = NULL;
	curr_node = node;
	while (i <= end)
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], "<") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<<") == 0)
		{
			if (!redir_node)
				redir_node = init_redir_node(curr_node, tokens, start, i);
			i += process_single_redirection(redir_node, tokens, i, end);
		}
		else
			i++;
	}
	if (redir_node)
		return (redir_node);
	return (curr_node);
}
