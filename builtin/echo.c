/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <anaroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:50:39 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/05 14:46:01 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	new_line_flag(char *arg)
{
	size_t	length;
	int i;
	
	length = ft_strlen(arg);
	if (length < 2)
		return (0);
	else if (length > 2)
	{
		if (arg[0] == '-' && arg[1] == 'n' && arg[2] != '\0')
		{
			i = 2;
			while (arg[i])
			{
				if (arg[i] != 'n')
					return (0);
				i++;
			}
			return (1);
		}
	}
	else if (arg && ft_strcmp(arg, "-n") == 0)
		return (1);
	return (0);
}



int	builtin_echo(t_data *data)
{
	int		i;
	int		n_flag;
	int		j;
	char	**quote_args;
	char	*env_var;

	//printf("we are here*************\n");
	i = 1;
	n_flag = 0;
	quote_args = NULL;
	// Check if the first argument is -n
	while (data->parsed->args[i] && new_line_flag(data->parsed->args[i]))
	{
		n_flag = 1;
		i++;
	}
	
	while (data->parsed->args[i])
	{
		if (data->parsed->args[i][0] == '$' && data->parsed->args[i][1] != '\0')
		{
			if (data->parsed->args[i][1] == '?')
			{
				exit_status_inside_string(data->parsed->args[i], data);
				i++;
				continue;
			}
			env_var = is_env_var(data->parsed->args[i], data);
			if (env_var)
				free(env_var);
			i++;
			continue;
		}
		if (data->parsed->args[i][0] == 39 || data->parsed->args[i][0] == 34)
		{
			quote_args = is_qoute(data->parsed->args[i]);
			if (data->parsed->args[i][0] == 34)
				check_env_var(quote_args, data);
			else
			{
				j = -1;
				while (quote_args[++j])
					printf("%s", quote_args[j]);
			}
			ft_free_ptr_array(quote_args);
			quote_args = NULL;
		}
		else if (data->parsed->args[i][0] == '$')
		{
			env_var = is_env_var(data->parsed->args[i], data);
			if (env_var)
				free(env_var);
		}
		// Check if argument is a quoted string
		else
			{
				if (!(find_exit_status(data->parsed->args[i])))
				{
					if (!data->parsed->args[i + 1] || data->parsed->args[i + 1][0] == 39 || data->parsed->args[i + 1][0] == 34)
					{
						printf("%s", data->parsed->args[i]);
					}
					else if (data->parsed->args[i + 1])
						printf("%s ", data->parsed->args[i]);
				}	// printf("%s!", data->parsed->args[i]);
				else
					exit_status_inside_string(data->parsed->args[i], data);
			}
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
