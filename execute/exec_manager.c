/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <anaroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:51:16 by anaroman          #+#    #+#             */
/*   Updated: 2025/08/06 13:11:32 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @file exec_manager.c
 * @brief Manages the execution flow of commands in the miniShell project.
 *
 * This function serves as the entry point for handling the execution of commands
 * within the miniShell program. It is responsible for coordinating the
 * execution process.
 */

// void execute(t_data *data)
// {
// 	t_parsed *cmd;


// 	if (!data || !data->parsed)
// 	{
// 		return;
// 	}
// 	cmd = data->parsed;

// 	t_parsed *suspect = data->parsed;
// 	while (suspect)
// 	{
// 	    if (ft_strcmp(suspect->args[0], "echo") == 0 && (suspect->redir_out || suspect->next || suspect->redir_in))
// 	        replace_echo_with_minishell_cmd(suspect);
// 	    suspect = suspect->next;
// 	}


// 	if(check_built_in(data)) //no redir echo stays here
// 	{
// 		// (&data);
// 		return;
// 	}
// 	construct_path(data, cmd);
// 	if (!cmd || !cmd->command)
// 	{
// 		data->exit_status = 127; // Command not found
// 		perror("Command not found\n"); // it is an empty command. Should do nothing?
// 		return;
// 	}

// 	// checks if command is a builtin and executes it
	

// 	// if not a builtin, execute it as a binary
// 	// side_binary_manager(data, cmd);
// 	if (cmd->next == NULL)
// 		side_binary_manager(data, cmd);
// 	else
// 		pipe_manager(data, cmd);
// }

bool check_redirections(t_parsed *cmd)
{
	// Check input file exists and is readable
	if (cmd->redir_in && access(cmd->redir_in, R_OK) == -1)
	{
		perror(cmd->redir_in);
		return (FAIL);
	}

	// Check output file (if it exists)
	if (cmd->redir_out && access(cmd->redir_out, F_OK) == 0)
	{
		// File exists → check writable
		if (access(cmd->redir_out, W_OK) == -1)
		{
			perror(cmd->redir_out);
			return (FAIL);
		}
	}
	// If file doesn't exist — don't fail, just let open() create it

	return (DONE);
}

bool setup_redirections(t_parsed *cmd)
{
	int fd;

	// Input redirection: if < file is specified
	if (cmd->redir_in)
	{
		fd = open(cmd->redir_in, O_RDONLY);
		if (fd == -1)
		{
			//perror("open redir_in");
			return FAIL;
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			//perror("dup2 redir_in");
			return FAIL;
		}
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
			//perror("open redir_out");
			return FAIL;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			//perror("dup2 redir_out");
			return FAIL;
		}
		close(fd);
		free(cmd->redir_out);
		cmd->redir_out = NULL;
	}

	return DONE;
}

bool setup_pipe_output(t_parsed *cmd)
{
	if (cmd->next)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_fd");
			return FAIL;
		}
		close(cmd->pipe_fd[1]);
		close(cmd->pipe_fd[0]);
	}
	return DONE;
}

bool is_builtin(t_parsed *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return false;

	return (
		ft_strcmp(cmd->args[0], "env")    == 0 ||
		ft_strcmp(cmd->args[0], "exit")   == 0 ||
		ft_strcmp(cmd->args[0], "echo")   == 0 ||
		ft_strcmp(cmd->args[0], "pwd")    == 0 ||
		ft_strcmp(cmd->args[0], "cd")     == 0 ||
		ft_strcmp(cmd->args[0], "export") == 0 ||
		ft_strcmp(cmd->args[0], "unset")  == 0
	);
}

int exec_builtin(t_data *data, t_parsed *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return 1;

	//printf("we are here************\n");
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return builtin_env(data);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return builtin_exit(data);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return builtin_echo(data);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return builtin_pwd(data);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return builtin_cd(data);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return builtin_export(data);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return builtin_unset(data);

	return 1;
}
void save_pipe_for_next(t_parsed *cmd)
{
	if (!cmd || !cmd->next)
		return;

	cmd->next->pipe_input = true;              // mark that the next cmd has input from pipe
	cmd->next->pipe_in_fd = cmd->pipe_fd[0];    // pass read-end to next command
	// Don't forget to close write-end in parent:
	close(cmd->pipe_fd[1]);
}


bool execution_manager(t_data *data, t_parsed *cmd)
{
	pid_t pid;

	//printf("****** %s\n", cmd->command);

	if (!cmd || !cmd->command || cmd->command[0] == '\0')
	{
		//data->exit_status = EXECNOTFOUND;
		data->exit_status = 1; 
		fprintf(stderr, "minishell: command not found\n");
		free_on_cmd_exit(&data);
		return FAIL;
	}

		if ((cmd->builtin && cmd->next) || ((cmd->builtin) && (cmd->redir_in || cmd->redir_out)))
	{

		if (cmd->next && pipe(cmd->pipe_fd) == -1)
		{
			perror("pipe");
			data->exit_status = 1;
			return FAIL;
		}

		pid = fork();
		if (pid < 0)
		{
			data->exit_status = 1;
			perror("minishell: fork failed");
			return FAIL;
		}


		if (pid == CHILD)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);

			// Set up pipe input if needed
			if (cmd->pipe_input)
			{
				dup2(cmd->pipe_in_fd, STDIN_FILENO);
				close(cmd->pipe_in_fd);
			}

			// Set up pipe output if piped to another command
			if (cmd->next)
			{
				if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 pipe_fd[1]");
					data->exit_status = 100;
					return (FAIL);
				}
				close(cmd->pipe_fd[0]);
				close(cmd->pipe_fd[1]);
			}

			if (setup_redirections(cmd) == FAIL)
				exit(FILE_ERR);
				//return (FAIL);

			if (is_builtin(cmd) && cmd->next)
			{
				//printf("we are here *************\n");
				data->exit_status = exec_builtin(data, cmd);
				exit(0);
			}
		
			cleanup_before_exec(cmd);
			execve(cmd->command, cmd->args, data->env_copy);
			perror("execve failed");
			free_on_cmd_exit(&data);
			exit(EXIT_FAILURE);
		}
		else // PARENT
		{
			cmd->pid1 = pid;
				

			// If there's a next command in the pipeline
			if (cmd->next)
			{
				// Pass the read-end of the current pipe to the next command
				cmd->next->pipe_input = true;
				cmd->next->pipe_in_fd = cmd->pipe_fd[0];
			
				// Parent no longer needs the write-end
				close(cmd->pipe_fd[1]);
			}
		
			// If this command was reading from a previous pipe, close that input now
			if (cmd->pipe_input)
				close(cmd->pipe_in_fd);
				
			return DONE;
		}

	}
	else if (cmd->builtin)
		data->exit_status = exec_builtin(data, cmd);
	return DONE;
}


bool restore_state(t_data *data)
{
	if (!data)
		return FAIL;

	if (dup2(data->stdin_backup, STDIN_FILENO) == -1)
	{
		perror("restore_state: dup2 stdin");
		return FAIL;
	}
	if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("restore_state: dup2 stdout");
		return FAIL;
	}

	return DONE;
}


bool execute(t_data *data)
{
	t_parsed *cmd;
	int status;

	if (!data || !data->parsed)
		return FAIL;

		
	cmd = data->parsed;

	//printf("\n****** %s\n", cmd->command);
	
	while (cmd)
	{
		if (check_redirections(cmd) == FAIL)
		{
			perror("minishell: redirection error");
			//printf("ready to return FAIL\n");
			return (FAIL);
		}
		if (execution_manager(data, cmd) == FAIL)
		{
			perror("minishell: execution failed");
			return FAIL;
		}
		 cmd = cmd->next;
	}
	//printf("***********we are here\n");
	// Wait for all child processes
	cmd = data->parsed;
	
	while (cmd)
	{
		if (cmd->pid1 > 0)
		{
			waitpid(cmd->pid1, &status, 0);
			if (cmd->next == NULL) // last command sets exit status
			{
				if (WIFEXITED(status))
					data->exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
				{
					int sig = WTERMSIG(status);
					data->exit_status = 128 + sig;
					if (sig == SIGINT)
						write(1, "\n", 1);
					else if (sig == SIGQUIT)
						write(1, "Quit (core dumped)\n", 19);
				}
			}
		}
		cmd = cmd->next;
	}

	//printf("");
	if (restore_state(data) == FAIL)
	{
		perror("minishell: restore state failed");
		return FAIL;
	}
	return DONE;
}
