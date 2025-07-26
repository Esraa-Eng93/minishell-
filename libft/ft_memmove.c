/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:39:56 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:40:03 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (d == s)
	{
		return (dest);
	}
	else if (d < s)
	{
		while (len--)
		{
			*d++ = *s++;
		}
		return (dest);
	}
	else
	{
		while (len--)
		{
			*(d + len) = *(s + len);
		}
		return (dest);
	}
}
/*
int main() {
    // Test 1: No overlap
    char source1[] = "Hello, world!";
    char dest1[20] = {0};

    printf("Before memmove (no overlap):\n");
    printf("Source: %s\n", source1);
    printf("Dest: %s\n", dest1);

    ft_memmove(dest1, source1, 13);

    printf("After memmove (no overlap):\n");
    printf("Source: %s\n", source1);
    printf("Dest: %s\n", dest1);

    // Test 2: Overlap, source before destination
    char source2[] = "Overlap example";
    char dest2[20] = {0};

    printf("\nBefore memmove (source before destination):\n");
    printf("Source: %s\n", source2);

    ft_memmove(dest2, source2, 16);

    printf("After memmove (source before destination):\n");
    printf("Dest: %s\n", dest2);

    // Test 3: Overlap, destination before source
    char buffer[20] = "Overlap example";

    printf("\nBefore memmove (destination before source):\n");
    printf("Buffer: %s\n", buffer);

    ft_memmove(buffer , buffer, 7); // Overlapping move

    printf("After memmove (destination before source):\n");
    printf("Buffer: %s\n", buffer);

    return 0;
}
*/
