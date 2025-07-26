/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:12:09 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:12:14 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[j])
		{
			while (needle[j] != '\0' && haystack[i + j]
				== needle[j] && i + j < len)
				j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
			else
				j = 0;
		}
		i++;
	}
	return (NULL);
}
/*
int main() {
    const char *haystack = "Hello, World!";
    const char *needle = "World";
    size_t len = 12; // نحدد النطاق الذي نبحث فيه
    char *result;

    result = ft_strnstr(haystack, needle, len);

    if (result != NULL) {
        printf("Found: %s\n", result); 
    } else {
        printf("Not Found\n");
    }

    return 0;
}

*/
