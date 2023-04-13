/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:54:44 by sawang            #+#    #+#             */
/*   Updated: 2022/11/03 17:54:05 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	char	*sub_str;

// 	i = 0;
//	//invalid operands to binary expression ('char **' and 'char *')
// 	while (i < len - start)
// 	{
// 		sub_str = (char *)malloc(sizeof(char));
// 		if (s[i + start] != '\0')
// 		{
// 			sub_str = sub_str + (char *)malloc(sizeof(char));
// 			sub_str[i - 1] = s[start];
// 			i++;
// 			start++;
// 		}
// 	}
// 	sub_str[i] = '\0';
// 	if (sub_str)
// 		return (sub_str);
// 	return (NULL);
// }

/**
 * @brief	Allocates (with malloc(3)) and returns a substring from the string ’s’.
 * The substring begins at index ’start’ and is of maximum size ’len’.
 * @param s: The string from which to create the substring.
 * @param start: The start index of the substring in the string ’s’.
 * @param len: The maximum length of the substring.
 * @details Need to consider if the start is larger than the string length,
 * or len is larger than the string length,
 * which means the maximum length of substring equals to s_len,
 * or for the substring to create allocate len + 1 memory,
 * which means substring is up to len and covers the rest testcases.
 * Need to malloc differnt size of memory for these three circumstances.
 * In the third case, we malloc more than what we need for the substr.
  * @return	The substring. NULL if the allocation fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
		substr = (char *)malloc(1);
	else if (len > s_len)
		substr = (char *)malloc(s_len - (size_t)start + 1);
	else
		substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && (size_t)start < s_len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
