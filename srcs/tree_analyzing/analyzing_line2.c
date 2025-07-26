/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_line2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:26:09 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/26 18:14:51 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	count_pipe_chars(const char *input, int i)
{
	int	count;

	count = 0;
	while (input[i + count] == '|')
		count++;
	return (count);
}

static char	*analyzing_pipes(const char *input, int *i)
{
	int		count;
	char	*err_token;
	char	*sub;

	count = count_pipe_chars(input, *i);
	if (count > 1)
	{
		err_token = ft_substr(&input[*i], 0, count);
		if (!err_token)
			return (NULL);
		(*i) += count;
		return (err_token);
	}
	else if (count == 1)
	{
		(*i)++;
		sub = ft_substr("|", 0, 1);
		if (!sub)
			return (NULL);
		return (sub);
	}
	return (NULL);
}

char	*analyzing_helper(int *i, char *cmp, int amount)
{
	char	*res;

	(*i) += amount;
	res = ft_substr(cmp, 0, 2);
	if (!res)
		return (NULL);
	return (res);
}

static char	*analyzin_redirections(const char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (analyzing_helper(i, "<<", 2));
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (analyzing_helper(i, ">>", 2));
	if (input[*i] == '>')
		return (analyzing_helper(i, ">", 1));
	if (input[*i] == '<')
		return (analyzing_helper(i, "<", 1));
	return (NULL);
}

char	*analyzing_pipes_redirections(const char *input, int *i)
{
	char	*pipes;
	char	*redirect;

	pipes = analyzing_pipes(input, i);
	if (pipes)
		return (pipes);
	redirect = analyzin_redirections(input, i);
	if (redirect)
		return (redirect);
	return (NULL);
}
