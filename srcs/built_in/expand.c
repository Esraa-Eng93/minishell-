/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:12:26 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:12:27 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*get_var_name(const char *input, int *i)
{
	int		var_len;
	char	*var_name;

	var_len = 0;
	var_name = malloc(100);
	if (!var_name)
		return (NULL);
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		var_name[var_len++] = input[*i];
		(*i)++;
	}
	var_name[var_len] = '\0';
	return (var_name);
}

static void	append_env_value(const char *env_value, char *new_str, int *j)
{
	while (*env_value)
		new_str[(*j)++] = *env_value++;
}

static void	handle_env_variable(const char *input, t_env *env,
				char *new_str, int *idx)
{
	const char	*env_value;
	char		*var_name;
	char		*exit_status_str;

	idx[0]++;
	if (input[idx[0]] == '?')
	{
		exit_status_str = ft_itoa(env->shell->exit_status);
		append_env_value(exit_status_str, new_str, &idx[1]);
		free(exit_status_str);
		idx[0]++;
		return ;
	}
	var_name = get_var_name(input, &idx[0]);
	if (!var_name)
		return ;
	env_value = get_env_value(env, var_name);
	if (env_value)
		append_env_value(env_value, new_str, &idx[1]);
	free(var_name);
}

char	*replace_env_variable(const char *input, t_env *env)
{
	int		idx[2];
	char	*new_str;

	idx[0] = 0;
	idx[1] = 0;
	new_str = malloc(1024);
	if (!new_str)
		return (NULL);
	while (input[idx[0]])
	{
		if (input[idx[0]] == '$' && input[idx[0] + 1] == '1')
			idx[0] += 2;
		else if (input[idx[0]] == '$' && input[idx[0] + 1] != '\0')
			handle_env_variable(input, env, new_str, idx);
		else
			new_str[idx[1]++] = input[idx[0]++];
	}
	new_str[idx[1]] = '\0';
	return (new_str);
}
