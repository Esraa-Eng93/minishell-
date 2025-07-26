/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:04:03 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/29 10:04:06 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DISCRIPTION:
appends the source string src to the end of the destination string dst,
 making sure that the total length of the resulting string
 does not exceed dstsize - 1 characters. 
It also ensures that the resulting string is null-terminated.
RETERN VALUE :
The length of the original destination string (strlen(dst))
 plus the length of the source string (strlen(src)).*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[i] && i < dstsize - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
