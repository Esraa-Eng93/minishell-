/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:59:40 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/05 13:59:42 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int,
char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void to_uppercase(unsigned int index, char *c) {
    (void)index; // الفهرس غير مستخدم هنا
    *c = (char)ft_toupper((unsigned char)*c);
}
  int main() {
    char str[] = "hello";

    // Case 1: Function pointer is valid
    ft_striteri(str, to_uppercase);
   
        printf("With function: %s\n", str);
       
  

    // Case 2: Function pointer is NULL
   ft_striteri(str, NULL);
    
        printf("Without function: %s\n", str);
        
  

    return 0;
}
*/
