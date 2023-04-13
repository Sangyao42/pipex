/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:57:26 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 19:51:44 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Applies the function ’f’ to each character of the string ’s’,
 * and passing its index as first argument to create a new string
 * (with malloc(3)) resulting from successive applications of ’f’.
 * @return	The string created from the successive applications of ’f’.
 * Returns NULL if the allocation fails.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	counter;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	counter = 0;
	while (s[counter])
	{
		result[counter] = f(counter, s[counter]);
		counter++;
	}
	result[counter] = 0;
	return (result);
}
