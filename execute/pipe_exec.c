/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:00:26 by anastasia         #+#    #+#             */
/*   Updated: 2025/08/04 14:22:38 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * !!!!!
 * while behaviour for 
 * ls -la | cat < test.txt
 * is identical to bash,
 * ls -la > txt.txt | cat < test.txt (with a redirection in the first command)
 * does not execute the redirection in the second pipe
 */

#include "../includes/minishell.h"

void side_binary_manager_in_pipe(t_data *data, t_parsed *cmd)
{
	int fd;

	// Input redirection: if < file is specified
	if (cmd->redir_in)
	{
		fd = open(cmd->redir_in, O_RDONLY);
		if (fd == -1)
		{
			perror("open redir_in");
			free_on_cmd_exit(&data);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(cmd->redir_in);
		cmd->redir_in = NULL;
	}

	// Output redirection: if > or >> is specified
	if (cmd->redir_out)
	{
		fd = open(cmd->redir_out, cmd->redir_flags, 0644);
		if (fd == -1)
		{
			perror("open redir_out");
			free_on_cmd_exit(&data);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		free(cmd->redir_out);
		cmd->redir_out = NULL;
	}

	// Finally, execute the command
	cleanup_before_exec(cmd);
	execve(cmd->command, cmd->args, data->env_copy);
	perror("execve failed");
	exit(EXIT_FAILURE);
}