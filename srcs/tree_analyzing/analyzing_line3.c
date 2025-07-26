/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_line3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:50:57 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/28 13:46:06 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*get_next_token(const char *input, int *i, t_env *env)
{
	static int	export_mode = 0;
	char		*token;

	skip_whitespace(input, i);
	if (input[*i] == '\0')
		return (NULL);
	token = handle_export_case(input, i, &export_mode);
	if (token)
		return (token);
	if (export_mode)
		return (export_assignment(input, i, &export_mode));
	token = handle_pipes_and_redirects(input, i);
	if (token)
		return (token);
	token = process_normal_token(input, i, env);
	if (!token)
		return (NULL);
	return (check_empty_token(token, input, i, env));
}

char	*check_empty_token(char *token,
		const char *input, int *i, t_env *env)
{
	if (ft_strspn(token, " \t") == ft_strlen(token) && env->quote_type == 0)
	{
		free(token);
		return (get_next_token(input, i, env));
	}
	return (token);
}

int	count_tokens(const char *input, t_env *env)
{
	int		count;
	int		i;
	char	*token;

	count = 0;
	i = 0;
	while (input[i])
	{
		token = get_next_token(input, &i, env);
		if (!token)
			break ;
		count++;
		free(token);
	}
	return (count);
}

char	**tokenize_input(const char *input, int token_count, t_env *env)
{
	int		i;
	int		count;
	char	**tokens;
	char	*token;

	i = 0;
	count = 0;
	tokens = mem_allocation(sizeof(char *) * (token_count + 1));
	while (input[i])
	{
		token = get_next_token(input, &i, env);
		if (!token)
			break ;
		tokens[count++] = token;
	}
	tokens[count] = NULL;
	return (tokens);
}

char	**split_line_command(const char *input, t_env *env)
{
	int		token_count;
	char	**tokens;

	if (!input)
		return (NULL);
	if (check_unclosed_quotes(input, env->shell))
		return (NULL);
	token_count = count_tokens(input, env);
	if (token_count == 0)
		return (NULL);
	tokens = tokenize_input(input, token_count, env);
	return (tokens);
}
