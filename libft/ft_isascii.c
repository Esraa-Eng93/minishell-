/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <ealshorm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:05 by ealshorm          #+#    #+#             */
/*   Updated: 2025/05/28 13:28:41 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION:
 checks if the passed character c falls within the ASCII character set, 
 which covers values from 0 to 127.
RETURN VALUE: 
A non-zero value is returned if c is an ASCII character, otherwise zero.
*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
