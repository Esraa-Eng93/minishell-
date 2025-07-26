/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshorm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:16:17 by ealshorm          #+#    #+#             */
/*   Updated: 2024/09/02 10:16:35 by ealshorm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = (char *)malloc(sizeof(char) * len);
	if (!ptr)
		return (NULL);
	ptr = ft_memcpy(ptr, s1, len);
	return (ptr);
}
/*
int main() {
    const char *original = "Hello, World!";
    char *copy = ft_strdup(original);

    if (copy != NULL) {
        printf("Original: %s\n", original);
        printf("Copy: %s\n", copy);
        free(copy); // Don't forget to free the memory
    } else {
        fprintf(stderr, "Failed to allocate memory for strdup\n");
    }

    return 0;
}
*/
