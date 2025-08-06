/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <anaroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:36:30 by anaroman          #+#    #+#             */
/*   Updated: 2025/08/06 12:36:34 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_builtin(t_data *data, t_parsed *cmd)
{
	int redirect_file;

	redirect_file = open(cmd->redir_out, cmd->redir_flags, 0644);
	if (redirect_file == -1)
	{
		perror(cmd->redir_out);
		// printf("Error opening file: %s\n", cmd->redir_out);
		data->exit_status = FILE_ERR;
		free_on_cmd_exit(&data);
		// exit(FILE_ERR);
		return;
	}
	dup2(redirect_file, STDOUT_FILENO);
	close(redirect_file);
	free(cmd->redir_out);
	cmd->redir_out = NULL;
	cleanup_before_exec(cmd);
} 

void no_redir_side_exec(t_data *data, t_parsed *cmd)
{
	pid_t pid;
	int status;

	//printf("\n************************** we are here\n");
	pid = fork();
	if (pid < 0)
	{
		//should we free ??
		perror("fork failed");
		return;
	}
	else if (pid == 0)
	{
		//printf("\n******!!!******************** we are here\n");
		// what is our cmd looks like here excactly?
		// everything except commands, args and env should be NULL
		// check if it is NULL
		signal(SIGINT, ctrl_c_handler);
		cleanup_before_exec(cmd);
		execve(cmd->command, cmd->args, data->env_copy);
		perror("execve failed");
		data->exit_status = 500;
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0); // wipe zombees
		//data->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);  // signal-based exit
		else if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);    // normal exit
	}
}
/**
 * all tredirection dunctions could be replaced with one
 * with a flag for the type of redirection
 */
void redir_out_side_exec(t_data *data, t_parsed *cmd)
{
	pid_t pid;
	int status;
	int redirect_file;

	redirect_file = open(cmd->redir_out, cmd->redir_flags, 0644);
	if (redirect_file == -1)
	{
		//perror(cmd->redir_out);
		//printf("Error opening file: %s\n", cmd->redir_out);
		data->exit_status = FILE_ERR;
		free_on_cmd_exit(&data);
		// exit(FILE_ERR);
		return;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		close(redirect_file);
		return; //++ clean up
	}
	else if (pid == 0)
	{
		dup2(redirect_file, STDOUT_FILENO);
		close(redirect_file);
		// check the exact structure of cmd here
		free(cmd->redir_out);
		cmd->redir_out = NULL;
		signal(SIGINT, ctrl_c_handler);
		cleanup_before_exec(cmd);
		execve(cmd->command, cmd->args, data->env_copy);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(redirect_file);
		waitpid(pid, &status, 0);
		//data->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);  // signal-based exit
		else if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);    // normal exit
	}
}

void dual_redir_exec(t_data *data, t_parsed *cmd)
{
	pid_t pid;
	int status;
	int input_fd = -1;
	int output_fd = -1;

	//printf("\n************************** we are here\n");
	if (cmd->redir_in)
	{
		input_fd = open(cmd->redir_in, O_RDONLY);
		if (input_fd == -1)
		{
			perror("Error opening input file");
			free_on_cmd_exit(&data);
			data->exit_status = FILE_ERR;
			return;
		}
	}

	if (cmd->redir_out)
	{
		output_fd = open(cmd->redir_out, cmd->redir_flags, 0644);
		if (output_fd == -1)
		{
			perror("output open failed");
			if (input_fd != -1)
				close(input_fd);
			free_on_cmd_exit(&data);
			data->exit_status = FILE_ERR;
			return;
		}
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		if (input_fd != -1)
			close(input_fd);
		if (output_fd != -1)
			close(output_fd);
		free_on_cmd_exit(&data);
		data->exit_status = FILE_ERR;
		return;
	}
	else if (pid == 0)
	{
		//printf("\n************************** we are here\n");
		if (input_fd != -1)
			dup2(input_fd, STDIN_FILENO);
		if (output_fd != -1)
			dup2(output_fd, STDOUT_FILENO);
		if (input_fd != -1)
			close(input_fd);
		if (output_fd != -1)
			close(output_fd);

		free(cmd->redir_in);
		cmd->redir_in = NULL;
		free(cmd->redir_out);
		cmd->redir_out = NULL;
		signal(SIGINT, ctrl_c_handler);

		execve(cmd->command, cmd->args, data->env_copy);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (input_fd != -1)
			close(input_fd);
		if (output_fd != -1)
			close(output_fd);
		waitpid(pid, &status, 0);
		//data->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);  // signal-based exit
		else if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);    // normal exit
	}
}
