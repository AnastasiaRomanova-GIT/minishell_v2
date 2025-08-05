/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:45:01 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 17:10:21 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_builtin_cmd(t_parsed *cmd)
{

	if (ft_strcmp(cmd->args[0], "cd") == 0
		|| ft_strcmp(cmd->args[0], "pwd") == 0
		|| ft_strcmp(cmd->args[0], "env") == 0
		|| ft_strcmp(cmd->args[0], "exit") == 0
		|| ft_strcmp(cmd->args[0], "echo") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0
		|| ft_strcmp(cmd->args[0], "unset") == 0)
	{
		cmd->builtin = true; // Mark as a builtin args[0]
	}
	else
	{
		cmd->builtin = false; // Not a builtin args[0]
	}
}
char	**args_copy(char **src, int count, int start)
{
    int len;
    
    len = 0;
    if (count == -1)
    {
        while (src[start + len])
            len++;
        count = len;
    }

    char **copy = malloc(sizeof(char *) * (count + 1));
    if (!copy)
        return NULL;

    for (int i = 0; i < count; i++)
        copy[i] = ft_strdup(src[start + i]);

    copy[count] = NULL;
    return copy;
}