/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:29:18 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 13:02:55 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool open_file(const char *filename, int flags)
{
	int fd;

	// printf("Attempting to open file: %s with flags: %d\n", filename, flags);
	if (!filename || filename[0] == '\0')
	{
		printf("Error: Invalid filename for redirection\n");
		return false;
	}
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror("Error opening file");
		return false;
	}
	close(fd); // Close the file descriptor immediately after opening
	return true;
}
char   *quoted_filename(char *str)
{
    char    **filename;
    char    *temp;

    if (!str || str[0] == '\0')
        return (NULL);

    if (str[0] == 39 || str[0] == 34)  // Single or double quote
    {
        filename = is_qoute(str);
        if (!filename)  // Check if is_qoute returned NULL
            return (NULL);
        if (!filename[0])  // Check if first element is NULL
        {
            ft_free_ptr_array(filename);
            return (NULL);
        }

        temp = ft_strdup(filename[0]);
        ft_free_ptr_array(filename);  // Free the entire array
        return (temp);
    }
    else  // Non-quoted case
        return (ft_strdup(str));
}
