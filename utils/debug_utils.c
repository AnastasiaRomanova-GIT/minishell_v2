/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <anaroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:47:04 by anaroman          #+#    #+#             */
/*   Updated: 2025/08/05 12:58:06 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_cmd(t_data *data)
{
	//int i;
	 t_parsed *cmd_print = data->parsed;
	 while (cmd_print)
	{
		printf("************************************************\n");
		if (cmd_print->command)
			printf("Command: %s\n", cmd_print->command);
		if (cmd_print->args)
		{
			printf("Args: ");
			for (int j = 0; cmd_print->args[j]; j++)
				printf("%s ", cmd_print->args[j]);

		}	
		printf("\n");
		if (cmd_print->redir_in)
			printf("Input Redirection: %s\n", cmd_print->redir_in);
		if (cmd_print->redir_out)
			printf("Output Redirection: %s\n", cmd_print->redir_out);
		if (cmd_print->redir_flags)
			printf("Redirection Flags: %d\n", cmd_print->redir_flags);
		if (cmd_print->next)
			printf("Next command exists\n");
		else
			printf("No next command\n");
		printf("************************************************\n");
		cmd_print = cmd_print->next;
	 }
	//i = 0;
	//while (data->inp_spltd[i])
	//	printf("splited data is :%s \n", data->inp_spltd[i++]);
	//printf("haha\n");
}
