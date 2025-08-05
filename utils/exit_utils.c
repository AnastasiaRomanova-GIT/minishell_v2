/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasia-romanova <anastasia-romanova@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:56:47 by anastasia         #+#    #+#             */
/*   Updated: 2025/08/04 23:13:48 by anastasia-r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Free the memory allocated for the data structure
 * before freeing the data structure, free all the allocated memory
 */
void free_on_program_exit(t_data **data)
{
	if ((*data)->input)
		free((*data)->input);
	if ((*data)->env_copy)
		ft_free_ptr_array((*data)->env_copy);
	if ((*data)->inp_spltd)
		ft_free_ptr_array((*data)->inp_spltd);
	if ((*data)->paths)
		ft_free_ptr_array((*data)->paths);
	if ((*data)->parsed)
		free_on_cmd_exit(data);
	if ((*data)->split)
		ft_free_ptr_array((*data)->split->splited);
	free(*data);
	close((*data)->stdin_backup);
	close((*data)->stdout_backup);
}

void free_on_cmd_exit(t_data **data)
{
	t_parsed *cmd;
	t_parsed *next;

	if (!data || !(*data)->parsed)
		return;
	cmd = (*data)->parsed;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->command)
			free(cmd->command);
		if (cmd->args)
		{
			ft_free_ptr_array(cmd->args);
			cmd->args = NULL;
		}
		if (cmd->redir_in)
			free(cmd->redir_in);
		if (cmd->redir_out)
			free(cmd->redir_out);
		if (cmd->pipe_fd[0] != -1 && cmd->pipe_fd[0] > 2)
			close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] != -1 && cmd->pipe_fd[1] > 2)
			close(cmd->pipe_fd[1]);
		free(cmd);
		cmd = next;
	}
	(*data)->parsed = NULL;
}

void cleanup_before_exec(t_parsed *cmd)
{
	if (cmd->redir_in)
	{
		free(cmd->redir_in);
		cmd->redir_in = NULL;
	}
	if (cmd->redir_out)
	{
		free(cmd->redir_out);
		cmd->redir_out = NULL;
	}
	if (cmd->next)
	{
		free(cmd->next);
		cmd->next = NULL;
	}
}
