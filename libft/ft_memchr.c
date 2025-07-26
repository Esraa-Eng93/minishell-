/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:08 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:42:14 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		i;

	str = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
/*
int main() {
    char buffer[] = "hello world";
    char *p = ft_memchr(buffer, 'o', sizeof(buffer));

    if (p != NULL) {
        printf("Found 'o' at position: %ld\n", p - buffer);
    } else {
        printf("'o' not found\n");
    }

    return 0;
}*/
