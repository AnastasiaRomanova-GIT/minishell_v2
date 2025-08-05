/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:26:33 by anastasia         #+#    #+#             */
/*   Updated: 2025/08/04 14:12:21 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void increment_shlvl(t_data *data)
{
	int i = 0;
	while (data->env_copy[i])
	{
		if (ft_strncmp(data->env_copy[i], "SHLVL=", 6) == 0)
		{
			int lvl = ft_atoi(&data->env_copy[i][6]);
			char *new_lvl = ft_itoa(lvl + 1);
			char *new_var = ft_strjoin("SHLVL=", new_lvl);
			free(data->env_copy[i]);
			data->env_copy[i] = ft_strdup(new_var);
			free(new_lvl);
			free(new_var);
			return;
		}
		i++;
	}
	// SHLVL not found → add it
}

void env_cpy(t_data *data, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	data->env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_copy)
		return;
	i = 0;
	while (envp[i])
	{
		data->env_copy[i] = ft_strdup(envp[i]);
		if (!data->env_copy[i])
		{
			while (--i >= 0)
				free(data->env_copy[i]);
			free(data->env_copy);
			return; // what to do/return here? Return SUCCESS or ERROR?
		}
		i++;
	}
	data->env_copy[i] = NULL;
	increment_shlvl(data);
}

void split_path(t_data *data)
{
	int i = 0;
	char *path_var = NULL;

	while (data->env_copy[i])
	{
		if (ft_strncmp(data->env_copy[i], "PATH=", 5) == 0)
		{
			path_var = data->env_copy[i] + 5;
			break;
		}
		i++;
	}
	if (!path_var)
		return;

	data->paths = ft_split(path_var, ':');
}

void construct_path(t_data *data, t_parsed *cmd)
{
    int i = 0;
    char *path_part = NULL;
    char *full_path = NULL;

    // Free existing command first to prevent leak
    if (cmd->command) {
        free(cmd->command);
        cmd->command = NULL;
    }

    // Handle cases where we can't find a valid command path
    if (!cmd->args || !cmd->args[0])
        return;

    // Handle absolute paths and relative paths
    if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.') 
{
        cmd->command = ft_strdup(cmd->args[0]);
        return;
    }

    // Handle missing PATH variable
    if (!data->paths)
        return;
    
    // Search through each path in PATH variable
    while (data->paths[i])
    {
        path_part = ft_strjoin(data->paths[i], "/");
        if (!path_part)
            return;  // Memory allocation failed

        full_path = ft_strjoin(path_part, cmd->args[0]);
        free(path_part);  // Free intermediate string immediately
        path_part = NULL;

        if (!full_path) 
            return;  // Memory allocation failed

        if (access(full_path, X_OK) == 0)
		{
            cmd->command = full_path;  // Transfer ownership to cmd->command
			full_path = NULL;
			return;
        }

        free(full_path);  // Free if not accessible
        full_path = NULL;
        i++;
    }
}