/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <anaroman>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:37:00 by anaroman          #+#    #+#             */
/*   Updated: 2024/10/16 21:10:36 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str_copy;
	int		i;

	i = 0;
	str_copy = (char *)malloc(ft_strlen(s) + 1);
	if (!str_copy)
		return (NULL);
	while (s[i] != '\0')
	{
		str_copy[i] = s[i];
		i++;
	}
	str_copy[i] = '\0';
	return (str_copy);
}
