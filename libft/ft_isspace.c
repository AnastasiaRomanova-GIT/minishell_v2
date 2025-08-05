/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:12 by anaroman          #+#    #+#             */
/*   Updated: 2024/06/13 13:13:12 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Mimics isspace
*/
// #include <ctype.h>

#include <stddef.h>
#include "libft.h"

int ft_isspace(char c)
{
	if (c == ' ') // || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v') && c != '\0')
	{
		return (8192);
	}
	else
	{
		return (0);
	}
}
