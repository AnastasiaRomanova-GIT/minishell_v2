/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:41:23 by anastasia         #+#    #+#             */
/*   Updated: 2025/08/01 19:04:51 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void ft_free_ptr_array(char **arr)
{
    // char **tmp;
    int i;
    
    i = 0;
    if (!arr)
        return;

    // tmp = arr;
    while (arr && arr[i])
    {
        free(arr[i]);
        arr[i] = NULL; // set to NULL to avoid dangling pointers
        i++;
    }
    free(arr);
    arr = NULL;
}