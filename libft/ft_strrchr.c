/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:56:04 by relgheit          #+#    #+#             */
/*   Updated: 2024/10/04 16:26:16 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*p;

	p = NULL;
	while (*str)
	{
		if (*str == (char)c)
			p = ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (p);
}
// #include <stdio.h>
// #include "ft"
// int main(void)
// {
// 	char s[] = "tripouille";
// 	/* 6 */ 
// 	char *s1 = ft_strrchr(s, 't' + 256);
// 	printf("%s \n", s1);
// 	return (0);
// }
