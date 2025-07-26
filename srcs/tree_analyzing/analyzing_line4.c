/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_line4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:02:56 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/27 12:04:34 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*handle_pipes_and_redirects(const char *input, int *i)
{
	return (analyzing_pipes_redirections(input, i));
}

static char	*process_token_content(const char *start,
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

static int	get_export_token_len(const char *input)
{
	int			j;
	char		quote;

	j = 0;
	while (input[j] && !ft_isspace(input[j]))
	{
		if (input[j] == '=')
		{
			j++;
			if (input[j] == '"' || input[j] == '\'')
			{
				quote = input[j++];
				while (input[j] && input[j] != quote)
					j++;
				if (input[j] == quote)
					j++;
			}
			else
				while (input[j] && !ft_isspace(input[j]))
					j++;
			break ;
		}
		j++;
	}
	return (j);
}

char	*export_assignment(const char *input, int *i,
		int *export_mode)
{
	const char	*start;
	int			j;
	char		*token;

	start = &input[*i];
	j = get_export_token_len(start);
	token = ft_substr(start, 0, j);
	if (!token)
		return (NULL);
	*i += j;
	*export_mode = 0;
	return (token);
}

char	*get_token_part(const char *input, int *i, t_env *env)
{
	const char	*start;
	int			length;
	int			disable_env;

	disable_env = 0;
	if (input[*i] == '"' || input[*i] == '\'')
		return (handle_quotes_if_needed(input, i, env, &disable_env));
	start = &input[*i];
	length = 0;
	while (input[*i] && !ft_isspace(input[*i])
		&& !ft_strchr("\"'|<>", input[*i]))
	{
		if (input[*i] == '\'')
			disable_env = 1;
		length++;
		(*i)++;
	}
	return (process_token_content(start, length, disable_env, env));
}
