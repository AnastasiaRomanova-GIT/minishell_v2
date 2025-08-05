/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasia-romanova <anastasia-romanova@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:56:10 by anaroman          #+#    #+#             */
/*   Updated: 2025/07/26 15:18:14 by anastasia-r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_int_is_null(void)
{
	char	*result;
	result = (char *)malloc(2);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}
static int	ft_count_digits(long temp)
{
	int	len;
	len = 0;
	while (temp != 0)
	{
		temp /= 10;
		len++;
	}
	return (len);
}
static char	*ft_negative_itoa(int len, long n_long)
{
	char	*result;
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	result[len + 1] = '\0';
	while (n_long != 0)
	{
		result[--len + 1] = (n_long % 10) + '0';
		n_long /= 10;
	}
	result[0] = '-';
	return (result);
}
static char	*ft_positive_itoa(int len, long n_long)
{
	char	*result;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (n_long != 0)
	{
		result[--len] = (n_long % 10) + '0';
		n_long /= 10;
	}
	return (result);
}
char	*ft_itoa(int n)
{
	int		len;
	long	n_long;
	n_long = n;
	if (n == 0)
		return (ft_int_is_null());
	if (n_long < 0)
	{
		n_long = -n_long;
		len = ft_count_digits(n_long);
		return (ft_negative_itoa(len, n_long));
	}
	len = ft_count_digits(n_long);
	return (ft_positive_itoa(len, n_long));
}