/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:14 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 14:03:16 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	handle_external_command(char **expanded_args,
		t_env **env, t_cmd *cmd)
{
	char	**exec_env;

	exec_env = create_env_array(*env);
	if (external_execution(expanded_args, env, exec_env, cmd) == FAILER)
	{
		free_exec_env(exec_env);
		free_tokens(expanded_args);
		(*env)->shell->exit_status = 1;
		return ((*env)->shell->exit_status);
	}
	free_exec_env(exec_env);
	free_tokens(expanded_args);
	return (SUCCESS);
}

static int	check_args_and_syntax(char **args,
		char **expanded_args, t_env **env)
{
	if (!expanded_args || !expanded_args[0])
	{
		ft_putendl_fd("minishell: no command entered", 2);
		(*env)->shell->exit_status = 127;
		free_tokens(expanded_args);
		return (127);
	}
	if (syntax_path(args, env) == 2)
	{
		free_tokens(expanded_args);
		return (2);
	}
	return (0);
}

static int	handle_empty_quotes(char **args, t_env **env)
{
	ft_putendl_fd("minishell: no command entered", 2);
	(*env)->shell->exit_status = 127;
	free_tokens(args);
	return (127);
}

int	minishell_execuation(char **args, t_env **env, t_cmd *cmd)
{
	int		builtin_status;
	int		check;
	char	**expanded_args;

	builtin_status = 42;
	expanded_args = expand_and_split_args(args, *env);
	if (!expanded_args || !expanded_args[0])
		return (handle_empty_quotes(expanded_args, env));
	check = check_args_and_syntax(args, expanded_args, env);
	if (check != 0)
		return (check);
	builtin_status = execute_builtin(args, env, cmd);
	if (builtin_status == FAILER)
	{
		free_tokens(expanded_args);
		return (FAILER);
	}
	if (builtin_status == SUCCESS)
	{
		free_tokens(expanded_args);
		return (SUCCESS);
	}
	return (handle_external_command(expanded_args, env, cmd));
}

int	execute_tree(t_cmd *node, t_env **env, t_shell *shell)
{
	(void)shell;
	if (!node)
		return (FAILER);
	if (node->type == PIPE)
	{
		if (execute_pipeline(node, env, shell) == FAILER)
			return (FAILER);
	}
	if (node->heredoce_count > 0 || node->input_file_count > 0
		|| node->output_file_count > 0 || node->append_file_count > 0)
	{
		if (execute_with_redirection(node, env, shell) == FAILER)
			return (FAILER);
	}
	if (node->type == COMMAND)
	{
		if (minishell_execuation(node->args, env, node) == FAILER)
			return (FAILER);
	}
	return (SUCCESS);
}
