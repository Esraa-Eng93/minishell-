/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:24:37 by snazzal           #+#    #+#             */
/*   Updated: 2025/06/03 14:24:23 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	add_output_file(t_cmd *cmd, const char *filename)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (cmd->output_file_count + 2));
	if (!new_array)
		return ;
	if (cmd->output_file)
	{
		while (i < cmd->output_file_count)
		{
			new_array[i] = cmd->output_file[i];
			i++;
		}
		free(cmd->output_file);
	}
	new_array[i++] = ft_strdup(filename);
	new_array[i] = NULL;
	cmd->output_file = new_array;
	cmd->output_file_count++;
}

void	add_append_file(t_cmd *cmd, const char *filename)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (cmd->append_file_count + 2));
	if (!new_array)
		return ;
	if (cmd->append_file)
	{
		while (i < cmd->append_file_count)
		{
			new_array[i] = cmd->append_file[i];
			i++;
		}
		free(cmd->append_file);
	}
	new_array[i++] = ft_strdup(filename);
	new_array[i] = NULL;
	cmd->append_file = new_array;
	cmd->append_file_count++;
}

void	add_input_file(t_cmd *cmd, const char *filename)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (cmd->input_file_count + 2));
	if (!new_array)
		return ;
	if (cmd->input_file)
	{
		while (i < cmd->input_file_count)
		{
			new_array[i] = cmd->input_file[i];
			i++;
		}
		free(cmd->input_file);
	}
	new_array[i++] = ft_strdup(filename);
	new_array[i] = NULL;
	cmd->input_file = new_array;
	cmd->input_file_count++;
}

int	is_valid_filename(char *filename)
{
	return (filename && filename[0] != '-' && filename[0] != '\0');
}
