/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:18:48 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 16:39:25 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_env_var(char **str, t_data *data)
{
	int	i;
	int	j;
	char	*env_var;
	
	i = -1;
	while(str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] != '$' || (str[i][j] == '$' && str[i][j + 1] == 0))
				printf("%c", str[i][j]);
			else if (str[i][j] == '$' && str[i][j + 1] == '?')
			{
				printf("%d", data->exit_status);
				j++;
			}
			else if (str[i][j] == '$' && str[i][j + 1] != 0)
			{
				env_var = is_env_var(&str[i][j], data);
				free(env_var);
				break;
			}
		}
	}
}

static	char	*ft_getenv(char *str, t_data *data)
{
	char	*env_var;
	int		i;
	size_t len;
	
	len = ft_strlen(str) - 1;
	env_var = NULL;
	while (str && *str && *str == '$')
		str++;
	i = 0;
	while (data->env_copy[i])
	{
		if (ft_strncmp(data->env_copy[i], str, len) == 0 && data->env_copy[i][len] == '=')
		{
			env_var = ft_strdup(data->env_copy[i] + len + 1);
			if (!env_var)
				return (NULL);
			return (env_var);
		}
		i++;
	}
	return (env_var);
}

char	*is_env_var(char *str, t_data *data)
{
	char *env_var;

	// printf("string is %s!\n", str);
	if (str[0] == '$' && !str[1])
	{
		printf("$");
		return (NULL);
	}
	env_var = ft_getenv(str, data);
	if (env_var)
		printf("%s", env_var);
	return (env_var);
	
}

char	**is_qoute(char *str)
{
	char	**temp;
	if (!str || str[0] == '\0')
		return (NULL);
	
	temp = NULL;
	if (str[0] == 39)
	{
		temp = ft_split(str, 39);
		if (!temp)
			return (NULL);
	}
	else if (str[0] == 34)
	{
		temp = ft_split(str, 34);
		if (!temp)
			return (NULL);
	}
	return (temp);
}
int	find_exit_status(char *str)
{
	size_t len;
	
	len = ft_strlen(str);
	
	if (ft_strnstr(str, "$?", len) != NULL)
	{
		printf("exit status found\n");
		return (1);
	}
	return (0);
	
}

void	exit_status_inside_string(char *str, t_data *data)
{
	int i;
	
	i = 0;
	while (str[i])
	{

		if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("%d", data->exit_status);
			i++;
		}
		else
			printf("%c", str[i]);
		i++;
	}
}
