/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:15:31 by sawang            #+#    #+#             */
/*   Updated: 2022/11/10 18:09:51 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Check if c is one character specified in the set.
*/
static int	char_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief	Allocates (with malloc(3)) and returns a copy of ’s1’
 * with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
 * @details	Use function ft_substr for creating the trimmed string.
 * @return	The trimmed string. NULL if the allocation fails.
 @set s1: string
 @set set: list characters to be trimmed
*/
/**
 *
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;

	i = 0;
	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	while (i < s1_len && char_in_set(s1[i], set))
		i++;
	while (s1_len > (i + 1) && char_in_set(s1[s1_len - 1], set))
		s1_len--;
	return (ft_substr(s1, i, s1_len - i));
}
// #include <stdio.h>

// int main(){
// 	char s[100] = "    \t\t\n\n hello world     \n\t";
// 	char set[20] = "\t\n ";
// 	printf("%s\n", ft_strtrim(s, set));
// }
