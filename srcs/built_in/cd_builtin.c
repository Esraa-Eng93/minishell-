/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:47 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:11:50 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	handle_cd_home(t_env **env)
{
	char	*home;

	home = get_env_value(*env, "HOME");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (FAILER);
	}
	chdir(home);
	return (SUCCESS);
}

static int	handle_cd_oldpwd(t_env **env)
{
	char	*oldpwd;

	oldpwd = get_env_value(*env, "OLDPWD");
	if (!oldpwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (FAILER);
	}
	chdir(oldpwd);
	return (SUCCESS);
}

int	process_cd_logic(char **args, t_env **env)
{
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (handle_cd_home(env) == FAILER)
		{
			(*env)->shell->exit_status = 1;
			return (FAILER);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (handle_cd_oldpwd(env) == FAILER)
		{
			(*env)->shell->exit_status = 1;
			return (FAILER);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("minishell: cd");
		(*env)->shell->exit_status = 1;
		return (FAILER);
	}
	return (SUCCESS);
}

int	handle_cd(char **args, t_env **env)
{
	char	cwd[1024];

	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		(*env)->shell->exit_status = 1;
		return (FAILER);
	}
	if (process_cd_logic(args, env) == FAILER)
		return (FAILER);
	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_value(env, "OLDPWD", get_env_value(*env, "PWD"),
			(*env)->shell);
		set_env_value(env, "PWD", cwd, (*env)->shell);
	}
	else
	{
		ft_putendl_fd("minishell: error retrieving current directory: getcwd: \
cannot access parent directories", 2);
		(*env)->shell->exit_status = 0;
		return (FAILER);
	}
	(*env)->shell->exit_status = 0;
	return (SUCCESS);
}
