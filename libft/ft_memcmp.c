/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:43:16 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:43:20 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	i = 0 ;
	ptr1 = s1;
	ptr2 = s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
		{
			return (ptr1[i] - ptr2[i]);
		}
		i++;
	}
	return (0);
}
/*
int main() {
    char buffer1[] = "hello";
    char buffer2[] = "hello";
    char buffer3[] = "world";

    int result = ft_memcmp(buffer1, buffer2, sizeof(buffer1));
    printf("Comparison result between buffer1 and buffer2: %d\n", result);
     // Expected output: 0

    result = ft_memcmp(buffer1, buffer3, sizeof(buffer1));
    printf("Comparison result between buffer1 and buffer3: %d\n", result); 
    // Expected output: a negative value

    return 0;
}*/
