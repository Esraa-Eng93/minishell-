/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:09 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:10 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	handle_exitstatus_expansion(char **result,
		const char *str, int *i, t_env *env)
{
	char	*exit_str;
	char	*tmp;

	(void)str;
	exit_str = ft_itoa(env->shell->exit_status);
	tmp = ft_strjoin(*result, exit_str);
	free(*result);
	*result = tmp;
	free(exit_str);
	*i += 2;
}

static void	handle_regular_char(char **result, const char *str, int *i)
{
	char	tmp[2];
	char	*tmp_result;

	tmp[0] = str[*i];
	tmp[1] = '\0';
	tmp_result = ft_strjoin(*result, tmp);
	free(*result);
	*result = tmp_result;
	(*i)++;
}

void	expand_exitstatus_in_line(char **line, t_env *env)
{
	char	*str;
	char	*result;
	int		i;

	str = *line;
	result = ft_strdup("");
	i = 0;
	if (!str || !env)
		return ;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			handle_exitstatus_expansion(&result, str, &i, env);
		else
			handle_regular_char(&result, str, &i);
	}
	free(*line);
	*line = result;
}
