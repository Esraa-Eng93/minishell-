/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:08:02 by snazzal           #+#    #+#             */
/*   Updated: 2025/06/03 14:08:51 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	is_redirection(char *token)
{
	return ((ft_strcmp(token, ">") == 0
			|| ft_strcmp(token, ">>") == 0
			|| ft_strcmp(token, "<") == 0
			|| ft_strcmp(token, "<<") == 0));
}

void	get_last_redirection_filename(char **tokens, t_cmd *node)
{
	int	i;

	i = 0;
	if (node->final_redirection)
	{
		free(node->final_redirection);
		node->final_redirection = NULL;
	}
	while (tokens[i])
	{
		if (is_redirection(tokens[i]) && tokens[i + 1])
		{
			if (ft_strcmp(tokens[i], "<") == 0)
				node->final_redir_type = REDIR_IN;
			else if (ft_strcmp(tokens[i], ">") == 0)
				node->final_redir_type = REDIR_OUT;
			else if (ft_strcmp(tokens[i], ">>") == 0)
				node->final_redir_type = APPEND_OUT;
			free(node->final_redirection);
			node->final_redirection = ft_strdup(tokens[i + 1]);
			i++;
		}
		i++;
	}
}

int	count_non_redir(char **tokens, int start, int end)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (i <= end)
	{
		if (is_redirection(tokens[i]) && (i + 1 <= end))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	copy_redir_arr(char **tokens, int start, int end, char **cmds)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (i <= end)
	{
		if (is_redirection(tokens[i]) && (i + 1 <= end))
			i += 2;
		else
		{
			cmds[j] = ft_strdup(tokens[i++]);
			if (!cmds[j])
				return (0);
			j++;
		}
	}
	return (1);
}

char	**fill_red_out_cmd(char **tokens, int start, int end)
{
	int		count;
	char	**red_out_cmd;

	count = count_non_redir(tokens, start, end);
	red_out_cmd = malloc(sizeof(char *) * (count + 1));
	if (!red_out_cmd)
		return (NULL);
	if (!copy_redir_arr(tokens, start, end, red_out_cmd))
		free_tokens(red_out_cmd);
	red_out_cmd[count] = NULL;
	return (red_out_cmd);
}
