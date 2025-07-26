/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:12:43 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:12:45 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_pwd_builtin(char **args, t_shell *shell)
{
	char	*path;

	(void)args;
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putendl_fd("minishell: error retrieving current directory: \
getcwd: cannot access parent directories", 2);
		shell->exit_status = 1;
		return (FAILER);
	}
	printf("%s\n", path);
	free(path);
	shell->exit_status = 0;
	return (SUCCESS);
}
