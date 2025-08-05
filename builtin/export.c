/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:06:38 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/01 14:33:35 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// Function to reallocate the env_copy array to a new size
char **realloc_env_copy(t_data *data, int new_size)
{
	char **new_env_copy;
	int i;

	if (!data->env_copy)
		return (NULL);
	// Allocate new memory for the resized array
	new_env_copy = malloc((sizeof(char *) * (new_size + 1))); 
	if (!new_env_copy)
	{
		printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	// Copy the existing environment variables to the new array
	i = 0;
	while (data->env_copy[i] && i < new_size - 1)
	{
		new_env_copy[i] = ft_strdup(data->env_copy[i]);
		free(data->env_copy[i]); // Free each old string
		i++;
	}
	new_env_copy[i] = NULL; // Null-terminate the new array
	free(data->env_copy); // Free the old env_copy array
	data->env_copy = new_env_copy; // Update the pointer
	return (new_env_copy);
}

// Function to find the index of a variable in the environment copy
int	find_var(t_data *data, char *new_var)
{
	int	i;
	int var_len;

	i = 0;
	var_len = 0;
	while (new_var[var_len] && new_var[var_len] != '=')
		var_len++; // Find the length of the variable name
	if (!data->env_copy || !new_var)
	{
		printf("Error: env_copy or new_var is NULL\n");
		return (-1);
	}
	
	while(data->env_copy[i] && (ft_strncmp(data->env_copy[i], new_var, var_len)))
		i++;
	if (data->env_copy[i] == NULL)
		return (-1); // Variable not found
	return(i);
}
// Function to export a variable to the environment copy
// ADD (Change variable value if it already exists)
// TOBE TESTED! 
int	builtin_export(t_data *data)
{
	int var_index;
	int env_size;

	env_size = 0;

	//UNCOMMENT TO FIX SEGFAULT & RECHECK LOGIC
	if (!data->parsed->args[1])
	{
		builtin_env(data);
		return (0);
	}
	
	if (num_check(data->parsed->args[1]) || strcmp(data->parsed->args[1], "=") == 0)
	{
		perror("export: not a valid identifier\n");
		return (1);
	}
	if (data->parsed->args[1] && ft_strrchr(data->parsed->args[1], '-'))
	{
		perror("not a valid identifier\n");
		return (1);
	}
	if (data->parsed->args[1] && ft_strrchr(data->parsed->args[1], '=') == NULL)
		return (0); // No variable to export, just return
	while (data->env_copy[env_size])
		env_size++; // Calculate the current size of env_copy
	if (!data->parsed->args[1])
		builtin_env(data);
	else
	{
		var_index = find_var(data, data->parsed->args[1]);
		if (var_index != -1)
		{
			// Variable found, update its value
			free(data->env_copy[var_index]);
			data->env_copy[var_index] = ft_strdup(data->parsed->args[1]);
		}
		else
		{
			// Variable not found, add a new entry
			if (realloc_env_copy(data, env_size + 2) == NULL)
				return (1);
			data->env_copy[env_size] = ft_strdup(data->parsed->args[1]);
			data->env_copy[env_size + 1] = NULL;
		}
	}
	return (0);
}
static void	delete_var(t_data *data, int var_index)
{
	if (data->env_copy[var_index])
	{
		free(data->env_copy[var_index]); // Free the variable string
		while (data->env_copy[var_index + 1]) // Shift left
		{
			data->env_copy[var_index] = data->env_copy[var_index + 1];
			var_index++;
		}
	}
}

int	builtin_unset(t_data *data)
{
	int var_index;
	int env_size;

	env_size = 0;
	while (data->env_copy[env_size])
		env_size++; // Calculate the current size of env_copy
	if (data->parsed->args[1] == NULL)
		return (0);
	else
	{
		var_index = find_var(data, data->parsed->args[1]);
		if (var_index != -1)
		{
			delete_var(data, var_index); // Delete the variable
			data->env_copy[env_size - 1] = NULL; // Null-terminate the array
		}
	}
	return (0);
}
// int main ()
// {
// 	t_data data;
// 	data.env_copy = malloc(3 * sizeof(char *));
// 	data.env_copy[0] = "PATH=/usr/bin";
// 	data.env_copy[1] = "HOME=/home/user";
// 	data.env_copy[2] = NULL;
// 	int index = find_var(&data, "HOME");
// 	if (index != -1)
// 	{
// 		printf("Variable found at index: %d\n", index);
// 	}
// 	else
// 	{
// 		printf("Variable not found.\n");
// 	}
// 	free(data.env_copy);
// 	return 0;
// }