/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:29:21 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 15:44:59 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	The memset() function writes len bytes of
 * value c (converted to an unsigned char) to the string b.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bc;

	bc = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		bc[i] = (unsigned char) c;
		i++;
	}
	return (bc);
}
