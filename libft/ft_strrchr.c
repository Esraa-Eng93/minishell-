/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:06:06 by ealshorm          #+#    #+#             */
/*   Updated: 2024/08/29 10:06:09 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Description: The strrchr function in C is used to find 
the last occurrence of a character in a string.
Return Value: the strrchr function returns a pointer 
to the last occurrence of the character c in the string str.
  */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (s[i] == (char)c)
		ptr = (char *)(s + i);
	return (ptr);
}
/*
int main(void) {
  const char *text = "esraa sherman";
  char *result = ft_strrchr(text, 'a');

  if (result) {
      printf("Found at position %d\n", result - text);
  } else {
      printf(" not found\n");}
  return 0;
*/
