/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:49:55 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 17:40:36 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Allocates (with malloc(3)) and returns a new string,
 * which is the result of the concatenation of ’s1’ and ’s2’.
 * @return	The new string. NULL if the allocation fails.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str_join;

	if (!s1 || !s2)
		return (NULL);
	str_join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str_join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str_join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str_join[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str_join[ft_strlen(s1) + i] = '\0';
	return (str_join);
}
