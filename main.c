/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:18:54 by snazzal           #+#    #+#             */
/*   Updated: 2025/06/03 13:21:28 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Include/minishell.h"

static void	handle_input_interrupt(t_shell *shell)
{
	if (g_recived_signals == SIGINT)
	{
		shell->exit_status = 130;
		g_recived_signals = 0;
	}
}

static int	free_syntax_logic(char **args, t_shell *shell)
{
	free_tokens(args);
	shell->exit_status = 2;
	return (FAILER);
}

static int	process_input(t_env **env, t_shell *shell, char *input)
{
	char	**args;
	t_cmd	*cmd2;
	int		i;

	args = split_line_command(input, *env);
	if (!args)
		return (FAILER);
	i = count_words(args) - 1;
	if (syntax_logic(args, 0, i) == SYNTAX_ERROR)
		return (free_syntax_logic(args, shell));
	cmd2 = tree_analyzing(args, 0, i, NULL);
	free_tokens(args);
	if (prepare_heredocs(cmd2, env) == FAILER)
	{
		free_cmd_tree(cmd2);
		return (FAILER);
	}
	if (execute_tree(cmd2, env, shell) == FAILER)
	{
		free_cmd_tree(cmd2);
		return (FAILER);
	}
	(*env)->quote_type = 0;
	free_cmd_tree(cmd2);
	return (SUCCESS);
}

void	run_the_shell(t_env **env, t_shell *shell)
{
	char	*input;

	(void)shell;
	while (1)
	{
		setup_signals(shell);
		input = readline(PROMPT);
		if (!input)
		{
			printf("Exit\n");
			break ;
		}
		handle_input_interrupt(shell);
		if (*input)
			add_history(input);
		if (process_input(env, shell, input) == FAILER)
		{
			free(input);
			continue ;
		}
		free(input);
	}
}

int	main(int ac, char **av, char **env_variables)
{
	t_env	*env;
	t_shell	shell;

	(void)av;
	if (ac > 1)
	{
		printf("Please don't enter any arguments\n");
		return (1);
	}
	shell.exit_status = 0;
	env = create_env_list(env_variables, &shell);
	set_env_value(&env, "0", "./minishell", &shell);
	set_env_value(&env, "1", "", &shell);
	run_the_shell(&env, &shell);
	free_env_list(env);
	return (shell.exit_status);
}
