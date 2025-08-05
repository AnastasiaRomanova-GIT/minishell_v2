/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <anaroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:46:11 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/05 13:43:47 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:57:06 by relgheit          #+#    #+#             */
/*   Updated: 2025/06/13 15:49:08 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// To compile this code, you need to link against the readline and history libraries.
// gcc minishell.c -o minishell -lreadline -lncurses

static void cp_input(char *input, t_data *data)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\n')
			break;
		i++;
	}
	data->input = (char *)malloc(sizeof(char) * (i + 1));
	if (!data->input)
		return;
	data->input[i] = '\0';
	while (--i >= 0)
		data->input[i] = input[i];
}

int input_read(t_data *data)
{
	const char *prompt = "minishell$ ";
	char *input = NULL;

	while (1)
	{
		input = readline(prompt);
		if (!input) // Ctrl+D
		// return (1);
		{
			printf("[debug] readline returned NULL. Exiting shell.\n");
			exit(data->exit_status);
		}

		if (input[0] == '\0') // empty line, prompt again
		{
			free(input);
			continue;
		}

		add_history(input);
		cp_input(input, data); // saves into data->input
		free(input);
		return (0); // success
	}
}

/**
 * main functionality for running the shell in a one-shot mode, which is 
 * important for automated testing
 */

/**
 * main should do
 * ********
 * show prompt
 * read line
 * if line is empty, show prompt again
 * if line is not empty, add it to history
 * tokenize the line
 * execute the command
 */
static void tester_compatibility(t_data *data, char **argv)
{
	int exit_code;
	
	data->input = ft_strdup(argv[2]);
	split_path(data);
	tokenize(data);
	execute(data);
	exit_code = data->exit_status;
	free_on_cmd_exit(&data);
	free_on_program_exit(&data);
	exit(exit_code);
}

int main(int argc, char **argv, char **envp)
{
	t_data *data;
	int exit_code = 0;
	(void)argv;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_memset(data, 0, sizeof(t_data)); // or use calloc

	env_cpy(data, envp); // copy envp to data->env_copy. Should it stay void?
	//split_path(data);	 // split PATH env variable into data->paths --------> Reconsider moving this function before executing commands or reuse it in execute()

	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);

	// auto-tester compatibility usage only
	if (argc == 3 && strcmp(argv[1], "-c") == 0)
		tester_compatibility(data, argv);

	if (argc > 1)
		printf("arguments ignored\n");

	// signal handlers
	signal(SIGQUIT, SIG_IGN);		// ctrl-\ does nothing
	signal(SIGINT, ctrl_c_handler); // ctrl-c breaks the command

	while (1)
	{
		split_path(data);
		if (input_read(data))
			break;
		if (check_string(data))
		{
			free_on_cmd_exit(&data);
			if (data->input)
				free(data->input);
			data->input = NULL;
			if (data->paths)
				ft_free_ptr_array(data->paths);
			data->paths = NULL;
			continue;
		}
		tokenize(data);
		if (DEBUG_MODE == 1)
			print_cmd(data);
		//printf("\n****** %s\n", data->parsed->command);
		execute(data);

		// make running cleanser function here
		ft_free_ptr_array(data->paths);
		data->paths = NULL;
		free_on_cmd_exit(&data);
	}
	exit_code = data->exit_status;
	free_on_cmd_exit(&data);
	free_on_program_exit(&data);
	return exit_code;
}
