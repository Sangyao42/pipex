/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:52:30 by sawang            #+#    #+#             */
/*   Updated: 2022/11/02 19:06:58 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

/**
 * @brief	Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
 * @details	Declare long new_n to avoid overflow MIN_INT.
 * Use % and / to get each digit of n from backwards.
 * @return	The string representing the integer. NULL if the allocation fails.
*/
char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	new_n;

	new_n = (long) n;
	len = int_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		new_n = -1 * (long)n;
	while (len >= 1)
	{
		str[len - 1] = new_n % 10 + '0';
		new_n = new_n / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
