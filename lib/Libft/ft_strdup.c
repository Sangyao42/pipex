/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:02:48 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 17:26:58 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 @brief	The strdup() function allocates sufficient memory
 for a copy of the string s1, does the copy, and returns a pointer to it.
 The pointer may subsequently be used as an argument to the function free(3).
 @details	string dup should be null-terminated.
 @return	If insufficient memory is available, NULL is returned
 and errno is set to ENOMEM.
*/
char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;

	dup = (char *)malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
