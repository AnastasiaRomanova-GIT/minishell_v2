/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:47:04 by anaroman          #+#    #+#             */
/*   Updated: 2025/08/01 11:46:35 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_cmd(t_data *data)
{
	int i;
	 t_parsed *cmd = data->parsed;
	 while (cmd)
	{
		printf("************************************************\n");
		if (cmd->command)
			printf("Command: %s\n", cmd->command);
		if (cmd->args)
			printf("Args: ");
		for (int j = 0; cmd->args[j]; j++)
			printf("%s ", cmd->args[j]);
		printf("\n");
		if (cmd->redir_in)
			printf("Input Redirection: %s\n", cmd->redir_in);
		if (cmd->redir_out)
			printf("Output Redirection: %s\n", cmd->redir_out);
		if (cmd->redir_flags)
			printf("Redirection Flags: %d\n", cmd->redir_flags);
		if (cmd->next)
			printf("Next command exists\n");
		else
			printf("No next command\n");
		printf("************************************************\n");
		cmd = cmd->next;
	 }
	  i = 0;
	  while (data->inp_spltd[i])
	  	printf("splited data is :%s \n", data->inp_spltd[i++]);
}