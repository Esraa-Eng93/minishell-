/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_line1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:10:50 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/27 12:08:05 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	get_quote_char(const char *input, int *i)
{
	return (input[(*i)++]);
}

static int	calculate_quoted_length1(const char *input, int *i, char quote)
{
	int	length;

	length = 0;
	while (input[*i] && input[*i] != quote)
	{
		length++;
		(*i)++;
	}
	return (length);
}

static char	*process_quoted_content(const char *start,
		int length, int disable_env, t_env *env)
{
	char	*substr;
	char	*expanded;

	substr = ft_substr(start, 0, length);
	if (!substr)
		return (NULL);
	if (!disable_env)
	{
		expanded = replace_env_variable(substr, env);
		free(substr);
		return (expanded);
	}
	return (substr);
}

char	*handle_quoted_token(const char *input, int *i,
		int *disable_env, t_env *env)
{
	char		quote;
	const char	*start;
	int			length;

	quote = get_quote_char(input, i);
	start = &input[*i];
	*disable_env = (quote == '\'');
	length = calculate_quoted_length1(input, i, quote);
	if (input[*i])
		(*i)++;
	return (process_quoted_content(start, length, *disable_env, env));
}

void	skip_whitespace(const char *input, int *i)
{
	while (ft_isspace(input[*i]))
		(*i)++;
}
