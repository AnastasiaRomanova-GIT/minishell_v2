/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:50:22 by relgheit          #+#    #+#             */
/*   Updated: 2024/10/01 15:13:37 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	b = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (b < len && big[b])
	{
		l = 0;
		while ((l + b) < len && little[l] && little[l] == big[b + l])
			l++;
		if (little[l] == 0)
			return ((char *)big + b);
		b++;
	}
	return (NULL);
}
// int main (void)
// {
// 	char *str = "hello world !!!";
// 	char *sub = "llo";
// 	printf("%s", ft_strnstr(str, sub, 5));
// }
