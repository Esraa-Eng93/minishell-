/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:29:28 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/27 12:29:24 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*error_message(int index)
{
	static char	*errors[8] = {
		"minishell: syntax error near unexpected token `|'\n",
		"minishell: syntax error near unexpected token `||'\n",
		"minishell: syntax error near unexpected token `newline'\n",
		"minishell: syntax error near unexpected token `operate'\n",
		": No such file or directory",
		"minishell : filename argument required",
		"command not found",
		"minishell: /: Is a directory"};

	return (errors[index]);
}

int	single_pipe_logic(char **tokens, int i, int start, int end)
{
	if (i == start || i == end)
	{
		ft_putstr_fd(error_message(0), 2);
		return (SYNTAX_ERROR);
	}
	if (ft_strcmp(tokens[i + 1], "|") == 0)
	{
		ft_putstr_fd(error_message(0), 2);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

int	pipe_logic(char **tokens, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			return (single_pipe_logic(tokens, i, start, end));
		}
		if (ft_strcmp(tokens[i], "||") == 0
			|| ft_strncmp(tokens[i], "||", 2) == 0)
		{
			ft_putstr_fd(error_message(1), 2);
			return (SYNTAX_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	path_error(char *arg, int error_index, t_env **env, int status)
{
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(error_message(error_index), 2);
	(*env)->shell->exit_status = status;
	return (2);
}

int	syntax_path(char **args, t_env **env)
{
	if (access(args[0], F_OK) != 0 && (args[0][0] == '/' || args[0][0] == '.'
			|| ft_strchr(args[0], '/')))
		return (path_error(args[0], 4, env, 127));
	else if (ft_strcmp(args[0], ".") == 0)
	{
		if (!args[1])
		{
			ft_putendl_fd(error_message(5), 2);
			(*env)->shell->exit_status = 2;
			return (2);
		}
	}
	else if (ft_strcmp(args[0], "..") == 0)
	{
		ft_putendl_fd(error_message(6), 2);
		(*env)->shell->exit_status = 127;
		return (2);
	}
	else if (ft_strcmp(args[0], "/") == 0)
	{
		ft_putendl_fd(error_message(7), 2);
		(*env)->shell->exit_status = 126;
		return (2);
	}
	return (0);
}
