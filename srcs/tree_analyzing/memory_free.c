/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:51:01 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/28 15:39:00 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens && tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_cmd_tree(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->left)
		free_cmd_tree(cmd->left);
	if (cmd->right)
		free_cmd_tree(cmd->right);
	if (cmd->args)
		free_tokens(cmd->args);
	if (cmd->input_file)
		free_tokens(cmd->input_file);
	if (cmd->output_file)
		free_tokens(cmd->output_file);
	if (cmd->append_file)
		free_tokens(cmd->append_file);
	if (cmd->heredoc_file)
		free_tokens(cmd->heredoc_file);
	if (cmd->heredoc_delimiter)
		free_tokens(cmd->heredoc_delimiter);
	if (cmd->red_out_cmd)
		free_tokens(cmd->red_out_cmd);
	if (cmd->final_redirection)
		free(cmd->final_redirection);
	free_env_list(cmd->env);
	free(cmd);
}

void	clean_all(t_cmd *cmd, t_env *env_list)
{
	if (env_list)
		free_env_list(env_list);
	if (cmd)
		free_cmd_tree(cmd);
}
