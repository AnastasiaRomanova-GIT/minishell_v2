/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:41:02 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 17:12:47 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./includes/minishell.h"

bool	check_redirection(t_data *data, char *s, int *i)
{
	char redir;
	int j;
	
	j = 1;
	redir = s[*i];
	if ((redir == '<' && s[*i + 1] == '>') || (redir == '>' && s[*i + 1] == '<'))
	{
		perror("Syntax Error\n");
		free_on_cmd_exit(&data);
		data->exit_status = 2;
		return (false);
	}
	(*i)++;
	while (s[*i] && s[*i] == redir)
	{
		j++;
		(*i)++;
	}
	(*i)--;
	if (j > 2)
	{
		perror("Syntax Error\n");
		free_on_cmd_exit(&data);
		data->exit_status = 2;
		return (false);
	}
	return (true);
}
bool	check_open_quote(t_data *data, char *s, int *i)
{
	char quote_char;

	quote_char = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote_char)
		(*i)++;
	if (s[*i] == quote_char)
		return (false);
	else
	{
		printf("Error: open quote\n");
		printf("Subject P.6 Paragraph.1\n");
		// free(data->input);
		data->input = NULL;
		free_on_cmd_exit(&data);
		return (true);
	}
}	

// RECHECK THE LOGIC
bool check_string(t_data *data)
{
	int i;

	i = 0;
	if (ft_strcmp(data->input, "$EMPTY") == 0)
	{
		// free_on_cmd_exit(&data);
		return (true);
	}
	while (data->input[i])
	{
		if (ft_ismeta(data->input[i]) || ft_isquote(data->input[i]))
		{
			if (data->input[i] == '<' || data->input[i] == '>')
			{
				if(check_redirection(data ,data->input, &i))
					return (false);
			}
			else if (ft_isquote(data->input[i]))
			{
				if (check_open_quote(data, data->input, &i))
					return (true);
			}
        }
        i++;
    }
	return (false);
}
