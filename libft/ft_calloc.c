/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:15:08 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:15:16 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	arr = malloc(count * size);
	if (arr == NULL)
	{
		return (NULL);
	}
	ft_memset(arr, 0, count * size);
	return (arr);
}
/*
int main() {
    int *arr;
    int n = 5;

    // Allocate memory for an array of 5 integers
    arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // All elements should be initialized to 0
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]); 
         // Expected output: 0 for all elements
    }

    // Free the allocated memory
    free(arr);

    return 0;
}
*/
