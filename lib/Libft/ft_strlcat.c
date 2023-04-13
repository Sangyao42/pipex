/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:17:15 by sawang            #+#    #+#             */
/*   Updated: 2022/10/21 22:36:23 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

// size_t	fk_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*(str + i) != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstsize != 0 && dstlen < dstsize)
	{
		while (src[i] != '\0' && i < (dstsize - dstlen - 1))
		{
			dst[dstlen + i] = src[i];
			i++;
		}
		dst[dstlen + i] = '\0';
		return (dstlen + srclen);
	}
	return (dstsize + srclen);
}

// int main(void)
// {
// 	// char dest[30]; memset(dest, 0, 30);
// 	// char * src = (char *)"AAAAAAAAA";

// 	// dest[0] = 'B';
// 	// ft_strlcat(dest, src, 1);

// 	char	b[0xF] = "nyan !";
// 	printf("%zu\n", ft_strlcat(NULL, b, 0));
// }
