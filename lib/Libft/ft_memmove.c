/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:48:05 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 17:27:55 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	The memmove() function copies len bytes from string src to string dst.
 * The two strings may overlap;
 * the copy is always done in a non-destructive manner.
 *
 * @details	Dealing with overlapping:
 * if dst is before src, copy from the beginning of src using memcpy;
 * if dst is behind src, copy from the end.
 *
 *@return	The memmove() function returns the original value of dst.
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;

	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (c_dst < c_src)
		c_dst = ft_memcpy(c_dst, c_src, len);
	else
	{
		while (len > 0)
		{
			c_dst[len - 1] = c_src[len - 1];
			len--;
		}
	}
	return (c_dst);
}

// int main(void)
// {
// 	char dst[] = "destination";
// 	char *src = dst + 4;
// 	//src = dst +4;

// 	printf("this is src : %s\n", src);
// 	printf("this is dst : %s\n", dst);
// 	memmove(dst, src,11);
// 	printf("this is rst : %s\n", dst);

// 	ft_memmove(dst, src, -1);
//	printf("this is my_rst: %s\n", dst);
// }
