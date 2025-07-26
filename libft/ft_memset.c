/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:36:41 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:36:51 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len--)
	{
		*ptr = c;
		ptr++;
	}
	return (b);
}
/*
int main() {
    char buffer[20]; // تعريف مصفوفة بحجم 20 بايت
    
    ft_memset(buffer, 'A', sizeof(buffer) - 1);

    
    buffer[sizeof(buffer) - 1] = '\0';

  
    printf("Buffer after ft_memset: %s\n", buffer);

    return 0;
}*/
