/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:21 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:22 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	restore_signal(void (*prev_sigint)(int))
{
	signal(SIGINT, prev_sigint);
}

void	handle_fork_failure(t_env *env, char *tmp_file)
{
	perror("fork failed");
	free(tmp_file);
	env->shell->exit_status = 1;
}

int	open_tmp_file(char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		perror("heredoc open");
	return (fd);
}

void	print_heredoc_eof_warning(char *delimiter)
{
	ft_putstr_fd("warning: heredoc delimited by EOF (wanted '", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	handle_heredoc_line(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}
