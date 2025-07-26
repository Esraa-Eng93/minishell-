/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:14:43 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/05 14:14:45 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*src;
	size_t	reslen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		reslen = ft_strlen(src) + 1;
	else
		reslen = len + 1;
	res = malloc(reslen * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, src, reslen);
	return (res);
}
/*
int main(void)
{
    char *result;

   
    result = ft_substr("Hello, World!", 7, 5);
    printf("Case 1: %s\n", result); 
    free(result);

    result = ft_substr("Hello, World!", 15, 5);
    printf("Case 2: %s\n", result); 
    free(result);

    result = ft_substr("Hello, World!", 7, 20);
    printf("Case 3: %s\n", result); 
    free(result);

    result = ft_substr("Hello, World!", 0, 5);
    printf("Case 4: %s\n", result);
    free(result);

    result = ft_substr("Hello, World!", 7, 0);
    printf("Case 5: %s\n", result);
    free(result);

    result = ft_substr(NULL, 0, 5);
    printf("Case 6: %s\n", result);
    free(result);

    result = ft_substr("Hello, World!", 13, 5);
    printf("Case 7: %s\n", result); 
    free(result);

    result = ft_substr("", 0, 5);
    printf("Case 8: %s\n", result);
    free(result);

    return 0;
}
*/
