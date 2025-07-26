/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:48 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:11:00 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = mem_allocation(sizeof(t_cmd));
	new_cmd->type = -1;
	new_cmd->args = NULL;
	new_cmd->input_file = NULL;
	new_cmd->output_file = NULL;
	new_cmd->append_file = NULL;
	new_cmd->heredoc_file = NULL;
	new_cmd->heredoc_delimiter = NULL;
	new_cmd->left = NULL;
	new_cmd->right = NULL;
	new_cmd->red_out_cmd = NULL;
	new_cmd->append_file_count = 0;
	new_cmd->input_file_count = 0;
	new_cmd->output_file_count = 0;
	new_cmd->final_redirection = NULL;
	new_cmd->final_redir_type = -1;
	new_cmd->heredoce_count = 0;
	new_cmd->fd_heredoc = -1;
	new_cmd->env = NULL;
	new_cmd->tmp_file = NULL;
	new_cmd->input_fd = 0;
	new_cmd->root = NULL;
	return (new_cmd);
}

t_env	*init_env(t_shell *shell)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		write(2, "Error:- Faild env Initialization\n", 34);
		return (NULL);
	}
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	node->quote_type = 0;
	node->shell = shell;
	node->cmd_pid = 0;
	return (node);
}
