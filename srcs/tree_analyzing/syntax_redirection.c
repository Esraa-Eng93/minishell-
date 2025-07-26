/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:27:07 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/27 12:29:08 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	syntax_logic(char **tokens, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (is_redirection (tokens[i]))
		{
			if (!tokens[i + 1] || tokens[i + 1][0] == '\0')
			{
				ft_putstr_fd(error_message(2), 2);
				return (SYNTAX_ERROR);
			}
			if (is_redirection(tokens[i + 1]))
			{
				ft_putstr_fd(error_message(3), 2);
				return (SYNTAX_ERROR);
			}
		}
		i++;
	}
	if (pipe_logic(tokens, start, end) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (SUCCESS);
}

void	add_heredoc_delimiter(t_cmd *node, const char *delimiter)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (node->heredoce_count + 2));
	if (!new_array)
		return ;
	if (node->heredoc_delimiter)
	{
		while (i < node->heredoce_count)
		{
			new_array[i] = node->heredoc_delimiter[i];
			i++;
		}
		free(node->heredoc_delimiter);
	}
	new_array[i++] = ft_strdup(delimiter);
	new_array[i] = NULL;
	node->heredoc_delimiter = new_array;
	node->heredoce_count++;
}
