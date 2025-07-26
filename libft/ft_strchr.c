/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:05:37 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/29 10:05:39 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
DEscription: The strchr function in C is used to find the first occurrence 
of a character in a string.
Return Value:
Returns a pointer to the first occurrence of the character c 
in the string str.
If the character is not found, it returns NULL.
*/
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}
/*
int main(void) {
  const char *text = "esraa";
  char *result = ft_strchr(text, 'e');

  if (result) {
      printf("Found at position %d\n", result - text);
  } else {
      printf(" not found\n");}
  return 0;
}*/
