/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:12:12 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:12:14 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	print_env_list(t_env *env_list, char **args)
{
	if (!env_list)
	{
		perror("env: environment is not available");
		return (FAILER);
	}
	if (!args[1])
	{
		while (env_list)
		{
			if (env_list->value != NULL)
				printf("%s=%s\n", env_list->key, env_list->value);
			env_list = env_list->next;
		}
		return (SUCCESS);
	}
	return (FAILER);
}

int	handle_env(t_env *env, char **args)
{
	if (print_env_list(env, args) == FAILER)
	{
		env->shell->exit_status = 1;
		return (FAILER);
	}
	env->shell->exit_status = 0;
	return (SUCCESS);
}
