/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:46 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/29 10:02:49 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION: 
function tests whether the passed character is a printable character.
RETURN VALUE: 
A non-zero value is returned if c is a printable character, otherwise zero.
*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
