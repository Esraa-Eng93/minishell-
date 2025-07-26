/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:05:19 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/29 10:05:22 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION:
 function converts the passed character to lowercase.
RETURN VALUE: 
The lowercase character is returned.
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z' )
		return (c + 32);
	return (c);
}
