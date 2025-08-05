/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaroman <anaroman>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:19:16 by anaroman          #+#    #+#             */
/*   Updated: 2024/09/20 13:19:16 by anaroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 30
#endif
#include <stdio.h> // for testing purposes
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int ft_isspace(char c);
int ft_isquote(char c);
int ft_ismeta(char c);
int ft_isdigit(int c);
void *ft_memset(void *s, int c, size_t n);
void ft_free_ptr_array(char **arr);
size_t ft_strlen(const char *str);
char **ft_split(char const *s, char c);
char *ft_strdup(const char *s);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
int ft_strcmp(char *s1, char *s2);
char *ft_strjoin(char const *s1, char const *s2);
char	*ft_strrchr(const char *str, int c);
// char **ft_split_token(char const *s); // --- IGNORE ---
int ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int	ft_atoi(const char *nptr);
int	ft_isalnum(int c);
char	*ft_itoa(int n);
int num_check(char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif // LIBFT_H
