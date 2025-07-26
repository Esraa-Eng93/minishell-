/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_line5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:06:31 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/27 12:07:06 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*handle_quotes_if_needed(const char *input,
			int *i, t_env *env, int *disable_env)
{
	if (input[*i] == '"' || input[*i] == '\'')
	{
		env->quote_type = input[*i];
		return (handle_quoted_token(input, i, disable_env, env));
	}
	return (NULL);
}

char	*handle_export_case(const char *input, int *i, int *export_mode)
{
	char	*token;

	if (!(*export_mode) && ft_strncmp(&input[*i], "export", 6) == 0
		&& ft_isspace(input[*i + 6]))
	{
		*export_mode = 1;
		*i += 6;
		token = ft_strdup("export");
		if (!token)
			return (NULL);
		return (token);
	}
	return (NULL);
}

char	*process_normal_token(const char *input, int *i, t_env *env)
{
	char	*joined;
	char	*part;
	char	*tmp;

	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	while (input[*i] && !ft_isspace(input[*i])
		&& !ft_strchr("|<>", input[*i]))
	{
		part = get_token_part(input, i, env);
		if (!part)
		{
			free(joined);
			return (NULL);
		}
		tmp = ft_strjoin(joined, part);
		free(joined);
		free(part);
		joined = tmp;
	}
	return (joined);
}
