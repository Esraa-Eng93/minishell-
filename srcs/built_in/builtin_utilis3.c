/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:39 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:11:40 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	update_existing_env(t_env *current, char *key, char *value)
{
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

t_env	*create_new_env_node(char *key)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		ft_putendl_fd("allocate to add new env node failed", 2);
		return (NULL);
	}
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		ft_putendl_fd("allocate to add env key failed", 2);
		return (NULL);
	}
	return (new_node);
}

int	assign_env_value(t_env *node, char *value)
{
	char	*trimmed;

	if (!value)
	{
		node->value = NULL;
		return (1);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		ft_putendl_fd("allocate to add env value failed", 2);
		return (0);
	}
	trimmed = ft_strtrim(node->value, " \t\n\v\f\r");
	if (!trimmed)
	{
		free(node->value);
		ft_putendl_fd("allocate to trim env value failed", 2);
		return (0);
	}
	free(node->value);
	node->value = trimmed;
	return (1);
}

void	add_node_to_env(t_env **env, t_env *new_node, t_shell *shell)
{
	new_node->next = *env;
	new_node->shell = shell;
	new_node->quote_type = 0;
	*env = new_node;
}

void	set_env_value(t_env **env, char *key, char *value, t_shell *shell)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	if (update_existing_env(current, key, value))
		return ;
	new_node = create_new_env_node(key);
	if (!new_node)
		return ;
	if (!assign_env_value(new_node, value))
	{
		free(new_node->key);
		free(new_node);
		return ;
	}
	add_node_to_env(env, new_node, shell);
}
