/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_trial.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:45:34 by anastasia-r       #+#    #+#             */
/*   Updated: 2025/08/04 14:18:59 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdlib.h>
#include <string.h>

// Joins all strings in a NULL-terminated array into a single space-separated string
static char *ft_strjoin_array(char **args)
{
    size_t total_len = 0;
    size_t i = 0;
    char *result;
    char *ptr;

    if (!args || !args[0])
        return strdup("");  // return empty string if no args

    // Calculate total length needed
    while (args[i])
    {
        total_len += ft_strlen(args[i]);
        if (args[i + 1])
            total_len += 1; // for space
        i++;
    }

    result = malloc(total_len + 1);
    if (!result)
        return NULL;

    ptr = result;
    i = 0;
    while (args[i])
    {
        size_t len = ft_strlen(args[i]);
        ft_memcpy(ptr, args[i], len);
        ptr += len;
        if (args[i + 1])
            *ptr++ = ' ';
        i++;
    }
    *ptr = '\0';

    return result;
}


void replace_echo_with_minishell_cmd(t_parsed *cmd)
{
    char *echo_line;
    char **new_args;

    // Build: echo hello > file   → "echo hello"
    echo_line = ft_strjoin_array(cmd->args);  // Build the "echo hello world" part
    
    new_args = malloc(sizeof(char *) * 4);
    new_args[0] = ft_strdup("./minishell");
    new_args[1] = ft_strdup("-c");
    new_args[2] = echo_line; // already allocated string
    new_args[3] = NULL;
    ft_free_ptr_array(cmd->args);
    cmd->args = new_args;
    // printf("here *******************\n");

    free(cmd->command);
    cmd->command = ft_strdup("./minishell");
}
