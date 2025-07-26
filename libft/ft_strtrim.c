/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:11:15 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/05 14:11:19 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (ft_is_in_set(s1[start], set))
		start++;
	if (start == end)
		return (ft_strdup(""));
	while (ft_is_in_set(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - start));
}
/*
int main(void)
{
    char *result;

    result = ft_strtrim("   Hello, World!  ", "  ");
    if (result != NULL)
    {
        printf("Trimmed: '%s'\n", result);
        free(result); 
    }
    else
    {
        printf("Memory allocation failed\n");
    }

    return (0);
}
*/
