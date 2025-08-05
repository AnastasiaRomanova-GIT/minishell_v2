/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasia-romanova <anastasia-romanova@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:50:19 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 20:13:47 by anastasia-r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>

#include "./structures.h"
#include "../libft/libft.h"
#include "./constants.h"

/**
 * Function prototypes
 */
void tokenize(t_data *data);
bool execute(t_data *data);
bool check_built_in(t_data *data);


// NEW TOKENIZE FUNCTIONS (TEST)

t_parsed	*create_pipe_struct(t_data *data, t_parsed *cmd);
void		ft_split_token(t_data *data);
void		count_word(t_split *split);
char		*word_dup(char *str, int start, int finish);
char		**args_copy(char **src, int count, int start);
void		split_s(t_split *split);
void		create_heredoc_file(t_data *data, const char *limiter);
void		init_cmd(t_parsed *cmd);
void		check_builtin_cmd(t_parsed *cmd);
int			calculate_pipes_count(char **inp_spltd);


// input functions
void env_cpy(t_data *data, char **envp);
void split_path(t_data *data);

// execution functions
void construct_path(t_data *data, t_parsed *cmd);
void side_binary_manager(t_data *data, t_parsed *cmd);
void no_redir_side_exec(t_data *data, t_parsed *cmd);
void redir_out_side_exec(t_data *data, t_parsed *cmd);
void dual_redir_exec(t_data *data, t_parsed *cmd);
void	redir_builtin(t_data *data, t_parsed *cmd);

// echo functions
void replace_echo_with_minishell_cmd(t_parsed *cmd);

// pipe functions
void pipe_manager(t_data *data, t_parsed *cmd);
void side_binary_manager_in_pipe(t_data *data, t_parsed *cmd);

// signal functions
void ctrl_c_handler(int sig);

// builtin functions
int builtin_env(t_data *data);
int builtin_pwd(t_data *data);
int builtin_cd(t_data *data);
int	builtin_export(t_data *data);
int builtin_exit(t_data *data);
int builtin_echo(t_data *data);
int	builtin_unset(t_data *data);

char **realloc_env_copy(t_data *data, int new_size);


// Echo utility functions
char **is_qoute(char *str);
char *is_env_var(char *str, t_data *data);
void check_env_var(char **str, t_data *data);
void	exit_status_inside_string(char *str, t_data *data);
int	find_exit_status(char *str);
int	find_var(t_data *data, char *new_var);
char   *quoted_filename(char *str);

// Error Check
bool    check_string(t_data *data);
bool    check_open_quote(t_data *data,char *s, int *i);
bool	check_redirection(t_data *data, char *s, int *i);
bool     open_file(const char *filename, int flags);


// clean-ups
void cleanup_before_exec(t_parsed *cmd);
void free_on_cmd_exit(t_data **data);
void free_on_program_exit(t_data **data);

// debug functions
void print_cmd(t_data *data);



#endif
