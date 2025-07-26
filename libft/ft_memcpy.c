/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:38:53 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:38:57 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	ptr = dest;
	ptr2 = src;
	if (!dest && !src)
		return (dest);
	while (n--)
	{
		*ptr = *ptr2;
		ptr++;
		ptr2++;
	}
	return (dest);
}
