/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:11 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:10:12 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*join_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	if (!full_path)
		return (NULL);
	free(temp);
	return (full_path);
}

static char	*try_executable_path(char *dir, char *cmd)
{
	char	*full_path;

	full_path = join_path(dir, cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_executable_in_path(char *cmd, char *path_value)
{
	char	*dir;
	char	*full_path;
	char	*start;
	char	*end;

	start = path_value;
	while (start)
	{
		end = ft_strchr(start, ':');
		if (end)
			dir = ft_substr(start, 0, end - start);
		else
			dir = ft_substr(start, 0, ft_strlen(start));
		if (!dir)
			return (NULL);
		full_path = try_executable_path(dir, cmd);
		free(dir);
		if (full_path)
			return (full_path);
		if (end)
			start = end + 1;
		else
			break ;
	}
	return (NULL);
}

char	*get_executable_path(char *cmd, t_env *env, char *path_value)
{
	path_value = get_env_value(env, "PATH");
	if (!path_value)
		return (NULL);
	return (search_executable_in_path(cmd, path_value));
}

void	increase_shlvl(t_env **env, char **args)
{
	char	*shell_value;
	int		shell_level;

	shell_value = get_env_value(*env, "SHLVL");
	if (!shell_value)
		shell_level = 0;
	else
		shell_level = ft_atoi(shell_value);
	if (ft_strcmp(args[0], "./minishell") == 0)
		shell_level++;
	shell_value = ft_itoa(shell_level);
	if (!shell_value)
		return ;
	set_env_value(env, "SHLVL", shell_value, (*env)->shell);
	free(shell_value);
}
