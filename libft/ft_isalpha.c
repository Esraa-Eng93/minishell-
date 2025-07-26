/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalpha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:16:13 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/26 09:28:59 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Description:
 function tests whether the passed character is an alphabetic letter.
Return value : 
A non-zero value is returned if c is an alphabetic letter, otherwise zero.
  */
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
int main()
{
  printf("%d\n", ft_isalpha('a'));
}*/
