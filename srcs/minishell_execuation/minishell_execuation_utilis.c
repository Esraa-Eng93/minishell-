/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execuation_utilis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:24 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:10:25 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	get_env_size(t_env *env)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

static char	*make_key_value(t_env *tmp)
{
	char	*key_value;
	char	*result;

	key_value = ft_strjoin(tmp->key, "=");
	if (!key_value)
		return (NULL);
	result = ft_strjoin(key_value, tmp->value);
	free(key_value);
	return (result);
}

static char	**free_env_array_on_error(char **env_array, int i)
{
	while (i > 0)
		free(env_array[--i]);
	free(env_array);
	return (NULL);
}

char	**create_env_array(t_env *env)
{
	int		size;
	char	**env_array;
	t_env	*tmp;
	int		i;

	size = get_env_size(env);
	env_array = malloc(sizeof(char *) * (size + 1));
	tmp = env;
	i = 0;
	if (!env_array)
		return (NULL);
	while (tmp)
	{
		env_array[i] = make_key_value(tmp);
		if (!env_array[i])
			return (free_env_array_on_error(env_array, i));
		i++;
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_exec_env(char **exec_env)
{
	int	i;

	if (exec_env)
	{
		i = 0;
		while (exec_env[i])
		{
			free(exec_env[i]);
			i++;
		}
		free(exec_env);
	}
}
