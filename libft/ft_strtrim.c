/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:04:26 by relgheit          #+#    #+#             */
/*   Updated: 2024/09/30 16:04:39 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		else
			set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*p;
	int		i;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_set(s1[start], set))
		start++;
	while (end > start && is_set(s1[end - 1], set))
		end--;
	p = malloc(sizeof(char) * ((end - start) + 1));
	if (!p)
		return (NULL);
	while (end > start)
	{
		p[i] = s1[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
// #include <stdio.h>
// int main()
// {
//     const char *str = "aabaaHello, world!abbaa";
// 	char const *set = "ab";
//     char *sub = ft_strtrim(str, set);

//     if (sub) {
//         printf("Substring: %s\n", sub);
//         free(sub); // Don't forget to free allocated memory
//     }

//     return 0;
// }