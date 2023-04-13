/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:47:27 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 16:48:12 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <unistd.h>
// #include <string.h>

/**
 * @brief	The memcmp() function compares byte string s1 against byte string s2.
 * Both strings are assumed to be n bytes long.
 * @return	returns zero if the two strings are identical,
 * otherwise returns the difference between the first two differing bytes
 * (eg., treated as unsigned char values, so that `\200' is greater than `\0').
 * Zero-length strings are always identical.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c_s1;
	unsigned char	*c_s2;
	size_t			i;
	int				ret_val;

	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	i = 0;
	ret_val = 0;
	while (i < n)
	{
		ret_val = c_s1[i] - c_s2[i];
		if (ret_val != 0)
			return (ret_val);
		else
			ret_val = 0;
		i++;
	}
	return (ret_val);
}

// void	ft_print_result(int n)
// {
// 	if (n > 0)
// 		write(1, "1", 1);
// 	else if (n < 0)
// 		write(1, "-1", 2);
// 	else
// 		write(1, "0", 1);
// }

// int		main(int argc, const char *argv[])
// {
// 	int		arg;

// 	alarm(5);
// 	if (argc == 1)
// 		return (0);
// 	else if ((arg = atoi(argv[1])) == 1)
// 	{
// 		ft_print_result(ft_memcmp("salut", "salut", 5));
// 		ft_print_result(memcmp("salut", "salut", 5));
// 	}
// 	else if (arg == 2)
// 	{
// 		ft_print_result(ft_memcmp("t\200", "t\0", 2));
// 		ft_print_result(memcmp("t\200", "t\0", 2));
// 	}
// 	else if (arg == 3)
// 	{
// 		ft_print_result(ft_memcmp("testss", "test", 5));
// 		ft_print_result(memcmp("testss", "test", 5));
// 	}
// 	else if (arg == 4)
// 	{
// 		ft_print_result(ft_memcmp("test", "tEst", 4));
// 		ft_print_result(memcmp("test", "tEst", 4));
// 	}
// 	else if (arg == 5)
// 	{
// 		ft_print_result(ft_memcmp("", "test", 4));
// 		ft_print_result(memcmp("", "test", 4));
// 	}
// 	else if (arg == 6)
// 	{
// 		ft_print_result(ft_memcmp("test", "", 4));
// 		ft_print_result(memcmp("test", "", 4));
// 	}
// 	else if (arg == 7)
// 	{
// 		ft_print_result(ft_memcmp("abcdefghij", "abcdefgxyz", 7));
// 		ft_print_result(memcmp("abcdefghij", "abcdefgxyz", 7));
// 	}
// 	else if (arg == 8)
// 	{
// 		ft_print_result(ft_memcmp("abcdefgh", "abcdwxyz", 6));
// 		ft_print_result(memcmp("abcdefgh", "abcdwxyz", 6));
// 	}
// 	else if (arg == 9)
// 	{
// 		ft_print_result(ft_memcmp("zyxbcdefgh", "abcdefgxyz", 0));
// 		ft_print_result(memcmp("zyxbcdefgh", "abcdefgxyz", 0));
// 	}
// 	else if (arg == 10)
// 	{
// 		ft_print_result(ft_memcmp("t\0\200", "t\0\0", 3));
// 		ft_print_result(memcmp("t\0\200", "t\0\0", 3));
// 	}
// 	return (0);
// }
