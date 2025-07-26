/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:12:32 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:12:35 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	handle_export_no_args(t_env **env)
{
	sort_export_list(*env);
	print_env(*env);
	(*env)->shell->exit_status = 0;
	return (SUCCESS);
}

static int	handle_export_without_equal(t_env **env, char *arg, int *error_flag)
{
	char	*key;

	key = remove_quotes(arg);
	if (!key || !is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("`: not a valid identifier", 2);
		free(key);
		*error_flag = 1;
		return (0);
	}
	set_env_value(env, key, NULL, (*env)->shell);
	free(key);
	return (0);
}

static void	handle_export_loop(t_env **env, char **args, int *error_flag)
{
	int		i;
	char	*equal_sign;

	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			handle_export_with_equal(env, args[i], error_flag);
		else
			handle_export_without_equal(env, args[i], error_flag);
		i++;
	}
}

int	handle_export(t_env **env, char **args)
{
	int	error_flag;

	error_flag = 0;
	if (!args[1])
		return (handle_export_no_args(env));
	handle_export_loop(env, args, &error_flag);
	sort_export_list(*env);
	(*env)->shell->exit_status = error_flag;
	return (SUCCESS);
}
