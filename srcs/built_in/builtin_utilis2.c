/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:37 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:11:38 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*remove_quotes(const char *str)
{
	int		i;
	int		j;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static int	swap_if_needed(t_env *current)
{
	char	*temp_key;
	char	*temp_value;

	if (ft_strcmp(current->key, current->next->key) > 0)
	{
		temp_key = current->key;
		temp_value = current->value;
		current->key = current->next->key;
		current->value = current->next->value;
		current->next->key = temp_key;
		current->next->value = temp_value;
		return (1);
	}
	return (0);
}

t_env	*sort_export_list(t_env *env_list)
{
	t_env	*temp_env_list;
	int		swapped;

	if (!env_list)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		temp_env_list = env_list;
		while (temp_env_list->next)
		{
			if (swap_if_needed(temp_env_list))
				swapped = 1;
			temp_env_list = temp_env_list->next;
		}
	}
	return (env_list);
}
