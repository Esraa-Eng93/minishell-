/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:30 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/30 15:20:58 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list->next;
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = temp;
	}
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static void	add_env_variable_line(t_env **env, char *str, t_shell *shell)
{
	char	*key_value;
	char	*equal_sign;

	key_value = ft_strdup(str);
	if (!key_value)
	{
		perror("failed memory allocation");
		return ;
	}
	equal_sign = ft_strchr(key_value, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		set_env_value(env, key_value, equal_sign + 1, shell);
	}
	free(key_value);
}

void	free_env_variable(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_env	*create_env_list(char **env_variables, t_shell *shell)
{
	t_env	*env;
	int		i;
	char	*temp;
	int		num;

	env = NULL;
	i = 0;
	while (env_variables[i])
	{
		if (ft_strchr(env_variables[i], '='))
			add_env_variable_line(&env, env_variables[i], shell);
		i++;
	}
	temp = get_env_value(env, "SHLVL");
	num = ft_atoi(temp) + 1;
	free_env_variable(&env, "SHLVL");
	temp = ft_itoa(num);
	if (temp)
	{
		set_env_value(&env, "SHLVL", temp, shell);
		free(temp);
	}
	return (env);
}
