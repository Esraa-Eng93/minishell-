/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:13:42 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 11:03:31 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
/*int main()
{
const char *str1 = "12345";
    const char *str2 = "   -6789";
    const char *str3 = "abc123";

    int num1 = ft_atoi(str1);  // Expected output: 12345
    int num2 = ft_atoi(str2);  // Expected output: -6789
    int num3 = ft_atoi(str3);  
    // Expected output: 0 (because "abc" is not a number)

    printf("str1 = %d\n", num1);
    printf("str2 = %d\n", num2);
    printf("str3 = %d\n", num3);

    return 0;
}*/
