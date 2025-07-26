/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:13:12 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/26 10:20:33 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 
Description: 
It tests whether the passed character c is a numeric digit (0 through 9).
Return value : 
A non-zero value is returned if c is a digit, otherwise zero.
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
