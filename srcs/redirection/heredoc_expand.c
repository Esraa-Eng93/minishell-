/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:09:06 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:07 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	handle_variable_expansion(const char *str, int i,
				char **result, t_env *env)
{
	int		j;
	char	*var_name;
	char	*value;
	char	*tmp;

	j = i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, i + 1, j - i - 1);
	value = get_env_value(env, var_name);
	tmp = ft_strjoin(*result, value);
	free(*result);
	*result = tmp;
	free(var_name);
	return (j);
}

static void	handle_char_append(const char *str, int *i, char **result)
{
	char	*c;
	char	*tmp;

	c = ft_substr(str, *i, 1);
	tmp = ft_strjoin(*result, c);
	free(*result);
	*result = tmp;
	free(c);
	(*i)++;
}

void	expand_variables_in_line(char **line, t_env *env)
{
	char	*str;
	char	*result;
	int		i;

	str = *line;
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			i = handle_variable_expansion(str, i, &result, env);
		else
			handle_char_append(str, &i, &result);
	}
	free(*line);
	*line = result;
}
