/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_helping_codes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snazzal <snazzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:40:24 by snazzal           #+#    #+#             */
/*   Updated: 2025/05/29 15:38:34 by snazzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_isspace(char c)
{
	if ((c == ' ') || (c == '\t'))
		return (1);
	return (0);
}

void	*mem_allocation(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
	{
		perror("Faild Memory allocation \n");
		exit(1);
	}
	return (ret);
}

int	count_words(char **str)
{
	int	count;

	count = 0;
	while (str[count] != NULL)
	{
		count++;
	}
	return (count);
}

int	check_unclosed_quotes(const char *input, t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	(void)shell;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == '\0')
			{
				ft_putendl_fd("syntax error: Use The Quote Correctly", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
