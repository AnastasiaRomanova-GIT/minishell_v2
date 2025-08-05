/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasia-romanova <anastasia-romanova@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:59:49 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 23:29:06 by anastasia-r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int builtin_env(t_data *data)
{
	int i;

	i = 0;
	if (data->env_copy)
	{
		while (data->env_copy[i])
			printf("%s\n", data->env_copy[i++]);
		return (0);
	}
	else
		return (1);
}



int builtin_pwd(t_data *data)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd failed");
		free_on_cmd_exit(&data);
		exit(1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}


int	no_file(t_data *data, char *path)
{
	
	if (chdir(path) == -1)
	{
		perror("No such file or directory");
		free(path);
		free_on_cmd_exit(&data);
		return (1);
	}
	return (0);
}

//  NEDDS Working on EDGE CASES
int builtin_cd(t_data *data)
{
	char *path;
	char *temp;
	int len;

	path = NULL;
	if (!data->parsed->args[1])
	{
		path = is_env_var("$HOME", data);
		chdir(path);
		return (0);
	}
	if (data->parsed->args[2])
	{
		perror("too many arguments");
		return (1);
	}
	if (ft_strcmp(data->parsed->args[1], "..") == 0)
	{
		path = getcwd(NULL, 0);
		temp = ft_strrchr(path, '/');
		len = (ft_strlen(path) - ft_strlen(temp));
		if (len < 0) //something is wrong with the type, but it does compile in my branch
		{
			free(path);
			perror("No such file or directory");
			free_on_cmd_exit(&data);
			return(1);
		}
		while(len++ < (int)ft_strlen(path))
			path[len] = '\0';
		if (no_file(data, path))
		{
			free(temp);	
			return (1);
		}
		free(path);
		return (0);
	}
	if (strcmp(data->parsed->args[1], "$PWD") == 0)
	{
		path = is_env_var("$PWD", data);
		if (no_file(data, path))
			return (1);
		free(path);
		return (0);
	}
	path = ft_strjoin(getcwd(NULL, 0), "/");
	path = ft_strjoin(path, data->parsed->args[1]);
	if (!path)
	{
		// perror("No such file or directory"); // this is not a good idea to print here, as it interferes with error codes later on
		free_on_cmd_exit(&data);
		return(1);
	}
	if (no_file(data, path))
		return (1);
	free(path);
	return (0);
}
