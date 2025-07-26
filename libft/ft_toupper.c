/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:56:52 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/29 11:57:03 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION:
 function converts the passed character to uppercase.
RETURN VALUE:
 The uppercase character is returned.
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z' )
		return (c - 32);
	return (c);
}
