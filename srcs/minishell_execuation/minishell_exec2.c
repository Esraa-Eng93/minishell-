/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:16 by ealshorm          #+#    #+#             */
/*   Updated: 2025/06/03 14:31:28 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	handle_simple_builtins(char **args, t_env **env, t_cmd *cmd)
{
	if (ft_strcmp(args[0], "echo") == 0)
	{
		ft_echo_builtin(args);
		(*env)->shell->exit_status = 0;
		return (SUCCESS);
	}
	else if (ft_strcmp(args[0], "env") == 0)
	{
		if (handle_env(*env, args) == FAILER)
			return (NOT_BUILTIN);
		return (SUCCESS);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		if (ft_pwd_builtin(args, (*env)->shell) == FAILER)
			return (FAILER);
		return (SUCCESS);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		my_exit(args, env, cmd);
		return (SUCCESS);
	}
	return (NOT_BUILTIN);
}

int	execute_builtin(char **args, t_env **env, t_cmd *cmd)
{
	int	result;

	result = handle_simple_builtins(args, env, cmd);
	if (result != NOT_BUILTIN)
		return (result);
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (handle_export(env, args) == FAILER)
			return (FAILER);
		return (SUCCESS);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		ft_unset(env, args);
		return (SUCCESS);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		if (handle_cd(args, env) == FAILER)
			return (FAILER);
		return (SUCCESS);
	}
	return (NOT_BUILTIN);
}

static void	handle_execve_failure(char **new_env, t_cmd *cmd,
				char **args, char **new_env2)
{
	ft_putendl_fd("command execution failed", 2);
	free_tokens(new_env);
	free_tokens(args);
	free_tokens(new_env2);
	free_cmd_tree(cmd);
	exit(126);
}

int	execute_with_absolute_or_relative_path(t_env **env,
		char **args, t_cmd *cmd, char **new_env2)
{
	char	**new_env;

	if (access(args[0], X_OK) == 0)
	{
		new_env = create_env_array(*env);
		if (execve(args[0], args, new_env) == -1)
		{
			free_env_list(*env);
			handle_execve_failure(new_env, cmd, args, new_env2);
		}
	}
	else
	{
		ft_putendl_fd(": Permission denied", 2);
		free_tokens(new_env2);
		clean_all(cmd, *env);
		exit(127);
	}
	return (0);
}

int	execute_with_path(char **args, t_env **env, char **exec_env, t_cmd *cmd)
{
	char	*cmd_path;

	cmd_path = get_executable_path(args[0], *env, NULL);
	if (cmd_path == NULL)
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("command not found ", 2);
		free_tokens(args);
		clean_all(cmd, *env);
		free_exec_env(exec_env);
		exit(127);
	}
	if (execve(cmd_path, args, exec_env) == -1)
	{
		ft_putendl_fd("command execution failed", 2);
		free(cmd_path);
		free_exec_env(exec_env);
		clean_all(cmd, *env);
		exit(1);
	}
	free(cmd_path);
	return (0);
}
