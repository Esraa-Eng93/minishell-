/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helping_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:22:50 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/27 13:08:27 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static size_t	count_args(char **list)
{
	size_t	i;

	i = 0;
	while (list && list[i])
		i++;
	return (i);
}

int	add_arg_to_list(char ***list, const char *arg)
{
	size_t	size;
	char	**new_list;
	size_t	i;

	size = count_args(*list);
	new_list = malloc(sizeof(char *) * (size + 2));
	if (!new_list)
		return (0);
	i = 0;
	while (i < size)
	{
		new_list[i] = (*list)[i];
		i++;
	}
	new_list[i++] = ft_strdup(arg);
	new_list[i] = NULL;
	free(*list);
	*list = new_list;
	return (1);
}

static char	**handle_expansion(char *arg, t_env *env, char **result)
{
	char	*expanded;
	char	**split;
	int		j;

	expanded = replace_env_variable(arg, env);
	if (!expanded)
		return (result);
	split = ft_split(expanded, ' ');
	free(expanded);
	if (!split)
		return (result);
	j = 0;
	while (split[j])
	{
		add_arg_to_list(&result, split[j]);
		j++;
	}
	free_tokens(split);
	return (result);
}

char	**expand_and_split_args(char **args, t_env *env)
{
	char	**result;
	size_t	i;

	result = NULL;
	i = 0;
	while (args[i])
	{
		result = handle_expansion(args[i], env, result);
		i++;
	}
	return (result);
}
