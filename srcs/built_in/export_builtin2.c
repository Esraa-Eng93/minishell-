/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:12:37 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:12:38 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	print_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value)
			printf("declare -x %s=%s\n", env_list->key, env_list->value);
		else
			printf("declare -x %s\n", env_list->key);
		env_list = env_list->next;
	}
}

static int	prepare_key_value(t_env **env, char *arg, char **key_value)
{
	char	*tmp;

	*key_value = ft_strdup(arg);
	if (!*key_value)
		return (FAILER);
	tmp = *key_value;
	*key_value = replace_env_variable(*key_value, *env);
	free(tmp);
	return (SUCCESS);
}

static int	process_key_value(t_env **env, char *arg,
				char *key_value, int *error_flag)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(key_value, '=');
	*equal_sign = '\0';
	key = remove_quotes(key_value);
	value = remove_quotes(equal_sign + 1);
	if (!key || !is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("`: not a valid identifier", 2);
		free(key_value);
		free(key);
		free(value);
		*error_flag = 1;
		return (0);
	}
	set_env_value(env, key, value, (*env)->shell);
	free(key_value);
	free(key);
	free(value);
	return (0);
}

int	handle_export_with_equal(t_env **env, char *arg, int *error_flag)
{
	char	*key_value;

	if (prepare_key_value(env, arg, &key_value) == FAILER)
	{
		perror("export: memory allocation failed");
		(*env)->shell->exit_status = 1;
		return (FAILER);
	}
	return (process_key_value(env, arg, key_value, error_flag));
}
