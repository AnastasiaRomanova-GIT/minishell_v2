/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:25:59 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 16:58:19 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	init_cmd(t_parsed *cmd)
{
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->redir_flags = 0;
	// cmd->next = NULL;
}

int calculate_pipes_count(char **inp_spltd)
{
	int	count;
	int	i;
	
	i = 0;
	count = 0;
	while (inp_spltd[i])
	{
		if (ft_strcmp(inp_spltd[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

t_parsed	*create_pipe_struct(t_data *data, t_parsed *cmd)
{
	t_parsed	*head;
	int			i;
	
	head = cmd;
	i = 0;

	while (i < data->pipes_count)
	{
		cmd->next = malloc(sizeof(t_parsed));
		if (!cmd->next)
        {
			ft_free_ptr_array(data->inp_spltd);
			return (NULL);
        }
		ft_memset(cmd->next, 0, sizeof(t_parsed));
		cmd = cmd->next;
		i++;
	}
	cmd->next = NULL; // Ensure the last command's next is NULL
	cmd = head; // Reset cmd to the head of the list
	return (cmd);
}
