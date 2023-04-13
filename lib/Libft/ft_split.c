/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:47:02 by sawang            #+#    #+#             */
/*   Updated: 2022/11/03 16:20:12 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include  <string.h>
// #include <stdio.h>

static int	str_counter(char const *s, char c)
{
	int	counter;

	counter = 0;
	if (!*s)
		return (counter);
	if (*s != c)
		counter++;
	while (*s)
	{
		s++;
		if (*s != c && *(s - 1) == c)
			counter++;
	}
	if (*s == '\0' && *(s - 1) == c)
		counter--;
	return (counter);
}

static char	**stringsfree(char **strings)
{
	char	**current;

	current = strings;
	while (*current)
	{
		free(*current);
		current++;
	}
	free(strings);
	return (NULL);
}

static char	**split_result(char const *s, char c, char **strings)
{
	int			len;
	int			index;
	char const	*old_s;

	index = 0;
	while (*s)
	{
		len = 0;
		while (*s == c)
			s++;
		if (!*s)
			break ;
		old_s = s;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		*(strings + index) = ft_substr(old_s, 0, len);
		if (!*(strings + index))
			return (stringsfree(strings));
		index++;
	}
	*(strings + index) = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (str_counter(s, c) + 1));
	if (!strings)
		return (NULL);
	strings = split_result(s, c, strings);
	return (strings);
}

// int	main(void)
// {
// 	char	*string = "r      split       this r";
// 	char	**expected = ((char*[6]){"split", "this", "for", "me", "!", NULL});
// 	char	**result = ft_split(string, ' ');
// 	// split_cmp_array(expected, result);
// 	printf("%s\n", result[0]);
// 	printf("%s\n", result[1]);
// 	printf("%s\n", result[2]);
// 	printf("%s\n", result[3]);
// 	printf("%s\n", result[4]);
// 	while (result)
// 	{
// 		result++;
// 	}
//  	char	**expected = ft_split("\0aa\0bbb", '\0');
//  	for (int i = 0; expected[i]; i++)
// 	{
// 		printf ("%d\n", i);
// 		printf("%s\n", expected[i]);
// 	}
// 	printf("%s\n", expected[0]);
// 	printf("%s\n", expected[1]);
// }
