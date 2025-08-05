/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:46:32 by anastasia-r       #+#    #+#             */
/*   Updated: 2025/08/04 17:21:29 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * test GNL function. Should be replaced with a real one from out projects
 */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*ft_strjoin_gnl(char *s1, char *s2, int len)
{
	char	*result;
	int		i = 0, j = 0;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	result = malloc(sizeof(char) * (i + len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (j < len)
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

// The main function to read the next line
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_pos = 0;
	static int	buffer_read = 0;
	char		*line = NULL;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		i = buffer_pos;
		while (i < buffer_read && buffer[i] != '\n') //the function must write immidiately at new line, no compilation up to buffer size
			i++;
		line = ft_strjoin_gnl(line, &buffer[buffer_pos], i - buffer_pos);
		if (!line)
			return (NULL);
		buffer_pos = i + 1;
		if (i < buffer_read && buffer[i] == '\n')
		{
			line = ft_strjoin_gnl(line, "\n", 1);
			break ;
		}
	}
	return (line);
}


void create_heredoc_file(t_data *data, const char *limiter)
{
    int fd = open(".tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Failed to create heredoc temp file");
        data->exit_status = 1;
        return;
    }

    char *line;
    while (1)
    {
        write(1, "mini-heredoc> ", 14); // prompt
        line = get_next_line(STDIN_FILENO);
        
        if (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
            write(fd, line, ft_strlen(line));
        if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
        {
            free(line);
            break;
        }
        free(line);
    }
    close(fd);
}
