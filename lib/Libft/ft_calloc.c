/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:43:47 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 21:31:01 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

/**
 * @brief	The calloc() function contiguously allocates
 * enough space for count objects that are
 * size bytes of memory each and returns a pointer to the allocated memory.
 * The allocated memory is filled with bytes of value zero.
 * @param	if count or size is 0, returns either NULL,
 * or a unique pointer value that can later be successfully passed to free().
*/
void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	mem = malloc(count * size);
	if (mem)
	{
		i = 0;
		while (i < (count * size))
		{
			mem[i] = 0;
			i++;
		}
		return (mem);
	}
	return (NULL);
}

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*temp;

// 	if (!count || !size)
// 	{
// 		count = 1;
// 		size = 1;
// 		//return (NULL);
// 	}
// 	if (size > (SIZE_MAX / count))
// 		return (NULL);
// 	temp = malloc(count * size);
// 	if (temp != 0)
// 		ft_memset(temp, 0, count * size);
// 	return (temp);
// }

// int main(void)
// {
// 		printf ("%zu\n", SIZE_MAX);
// 		// char *str1 = (char *)malloc(SIZE_MAX);
// 		// if (str1)
// 		// {
// 		// 	printf("%c\n", str1[0]);
// 		// 	printf("%zu\n", strlen(str1));
// 		// 	free(str1);
// 		// }
// 		char *str2 = ft_calloc(2, 2);
// 		char to_cmp[] = {0, 0, 0, 0};
// 		if (str2)
// 		{
// 			if(memcmp(str2, to_cmp, 4) == 0)
// 				printf("correct\n");
// 			else
// 				printf("wrong\n");
// 			free(str2);
// 		}
// 		// char *str3 = ft_calloc(1, 0);
// 		char *str3_1 = calloc(1, 0);
// 		if (/*str3 &&*/ str3_1)
// 		{
// 			// if(memcmp(str3, str3_1, 0))
// 			// 	printf("correct");
// 			// if (memcmp(str3, str3_1, 1))
// 			// 	printf("check?");
// 			// else
// 			// 	printf("wrong");

// 			printf("%p\n", str3_1);
// 			printf("%zu\n", sizeof(char));
// 			// free(str3);
// 			free(str3_1);
// 		}
// 		else
// 			printf(NULL);
// 		// char *str4 = ft_calloc(0, 0);
// 		// if (str4)
// 		// {
// 		// 	printf("%zu\n", strlen(str4));
// 		// 	printf("%s\n", str4);
// 		// 	free(str4);
// 		// }
// 		// else
// 		// 	printf(NULL);
// }
