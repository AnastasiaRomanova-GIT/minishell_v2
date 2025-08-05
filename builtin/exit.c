/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:39:41 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/01 18:34:30 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_exit(t_data *data)
{

	if (!data->parsed->args[1])
	{
		data->exit_status = 0;
		free_on_program_exit(&data);
		exit(0);
	}
	
	if (data->parsed->args[2])
	{
		perror(" too many arguments\n");
		data->exit_status = 1;
		return (1);
	}
	else if (data->parsed->args && data->parsed->args[1]) //args[1] = optional exit code
    {
		if (!(num_check(data->parsed->args[1])))
		{
			data->exit_status = 2;
			perror("numeric argument required\n");
			free_on_program_exit(&data);
			exit(2);
		}

        if (data->parsed->args[1] && (num_check(data->parsed->args[1]) == 1))
		{	
			data->exit_status = ft_atoi(data->parsed->args[1]);  // convert string to int
        // Optionally, add error handling if args[1] is not a valid number
			free_on_program_exit(&data);
			exit(data->exit_status); // Exit with the status code, ensuring it's within 0-255
		// ADD Module to handle exit status > 256
		}
		
		else 
		{
			free_on_program_exit(&data);
			exit(0);
		}
    }
	return(0);
}
