/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/04 17:22:31 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

/***the function just takes the size of the original
 *array and allocates a new one of the same size
 *therefore extra memory is allocated
 */




t_parsed	*collect_args(t_parsed *cmd, t_data *data, int *cur_ind, int start)
{
    if (cmd->arg_count > 0)
    {
        int arg_index = 0;
		char **str;
		
		str = data->inp_spltd;
		*cur_ind = start;  // Reset to start of command
        cmd->args = malloc(sizeof(char *) * (cmd->arg_count + 1));
        if (!cmd->args)
        {
            free_on_cmd_exit(&data);
            return (NULL);  // Memory allocation failed
        }
        while (str[*cur_ind] && ft_strcmp(str[*cur_ind], "|") != 0)
        {
            if (ft_strcmp(str[*cur_ind], ">") == 0 ||
				ft_strcmp(str[*cur_ind], ">>") == 0 ||
                ft_strcmp(str[*cur_ind], "<") == 0 ||
                ft_strcmp(str[*cur_ind], "<<") == 0)
                (*cur_ind) = (*cur_ind) + 2;  // Skip redirection token & filename
            else
            {
                cmd->args[arg_index] = ft_strdup(str[*cur_ind]);
                arg_index++;
                (*cur_ind)++;
            }
        }
        cmd->args[arg_index] = NULL;  // NULL-terminate args array
    }
    return (cmd);
}
 



t_parsed *single_command_struct(t_data *data, t_parsed *cmd, int *current_index)
{
    int start;
	char *filename;
	int file_err;
	
	start = *current_index;
    cmd->arg_count = 0;
	file_err = 0;
	filename = NULL;
    // First pass: count valid arguments and handle redirections
    while (data->inp_spltd[*current_index] && 
           ft_strcmp(data->inp_spltd[*current_index], "|") != 0)
    {
        if (ft_strcmp(data->inp_spltd[*current_index], ">") == 0 ||
            ft_strcmp(data->inp_spltd[*current_index], ">>") == 0)
        {
			filename = quoted_filename(data->inp_spltd[*current_index + 1]);
            if (ft_strcmp(data->inp_spltd[*current_index], ">>") == 0)
                cmd->redir_flags = O_WRONLY | O_CREAT | O_APPEND;
            else if (ft_strcmp(data->inp_spltd[*current_index], ">") == 0)
                cmd->redir_flags = O_WRONLY | O_CREAT | O_TRUNC;
            if(open_file(filename, cmd->redir_flags) && !file_err)
            {
                if (cmd->redir_out)
                    free(cmd->redir_out);
                cmd->redir_out = ft_strdup(filename);
				// printf("Output redirection file: %s\n", cmd->redir_out);
                (*current_index)++;  // Skip filename
            }
            else
            {
                file_err = 1; // Set error flag to indicate file opening failure
                    if (cmd->redir_out)
                        free(cmd->redir_out);
                cmd->redir_out = ft_strdup(filename);
                data->exit_status = 1; // Set exit status to indicate error
                // return (NULL); // Return NULL to indicate error
            }
        }
        else if (ft_strcmp(data->inp_spltd[*current_index], "<") == 0)
        {
            cmd->redir_in = quoted_filename(data->inp_spltd[*current_index + 1]);
                // printf("Input redirection file: %s\n", cmd->redir_in);
            (*current_index)++;  // Skip filename
        }
        else if (ft_strcmp(data->inp_spltd[*current_index], "<<") == 0)
        {
            char *limiter = data->inp_spltd[*current_index + 1];
            if (!limiter || limiter[0] == '\0')
            {
                perror("syntax error near unexpected token `newline'");
                data->exit_status = 1;
                return NULL; //and it segfaults later on?
            }
            create_heredoc_file(data, limiter);
            cmd->redir_in = ft_strdup(".tmp_file");
            (*current_index)++;  // skip limiter
        }
        else
            cmd->arg_count++; // Count regular arguments
        (*current_index)++;
		if (filename)
			free(filename); // Free filename after use
		filename = NULL; // Reset filename for next iteration
    }
	
    // Second pass: collect arguments
    cmd = collect_args(cmd, data, current_index, start);
	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
    return (cmd);
}
 
 
void tokenize(t_data *data)
{
    t_parsed	*cmd;
	t_parsed	*head;
    int 		i;
	
	cmd = malloc(sizeof(t_parsed));
    ft_memset(cmd, 0, sizeof(t_parsed));
	i = 0;

    if (!cmd)
        return;
    ft_split_token(data);
    if (!data->inp_spltd || !data->inp_spltd[0])
    {
		free_on_cmd_exit(&data);
        return;
    }
	head = cmd;
	data->pipes_count = calculate_pipes_count(data->inp_spltd);

	if (data->pipes_count > 0)
		cmd = create_pipe_struct(data, cmd);
	while (cmd)
	{
        init_cmd(cmd);
		cmd = single_command_struct(data, cmd, &i);
        check_builtin_cmd(cmd);
    	if (cmd)  // Only process if cmd is valid
        {
            construct_path(data, cmd);
            if (data->inp_spltd[i] && ft_strcmp(data->inp_spltd[i], "|") == 0)
                i++;
        }
		cmd = cmd->next; // this one needs to be in final tokenize
	}
	if (data->inp_spltd)
    {
        ft_free_ptr_array(data->inp_spltd);
        data->inp_spltd = NULL;
    }
	cmd = head; // Reset cmd to the head of the list
    data->parsed = cmd; // Set the head of the parsed linked list
}
