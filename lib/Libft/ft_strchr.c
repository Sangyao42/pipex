/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:18:06 by sawang            #+#    #+#             */
/*   Updated: 2022/11/13 22:43:20 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strchr() function locates the first occurrence of
 * c (converted to a char) in the string pointed to by s.
 * The terminating null character is considered to be part of the string;
 * therefore if c is `\0', the functions locate the terminating `\0'.
*/
char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	str = (char *)s;
	s_len = ft_strlen(str);
	if ((char) c == 0)
		return (&str[s_len]);
	i = 0;
	while (str[i] != '\0' )
	{
		if (str[i] == (char) c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
