/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:15:35 by relgheit          #+#    #+#             */
/*   Updated: 2025/07/28 14:17:47 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static int int_limits(const char *str)
{
	long long int result;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if ((result >= 0) && (result < INT_MAX))
		return (1);
	else
		return (0);
}


int num_check(char *src)
{
	int i;
	i = 0;
	if (!src || !*src)
		return (0);
	if (src[i] == '-')
		i++;
	while (src[i] != '\0')
	{
		if ((ft_isdigit(src[i]) == 0))
			return (0);
		i++;
	}
	if (int_limits(src) == 0)
		return (0);
	return (1);
}