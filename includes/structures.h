/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasia-romanova <anastasia-romanova@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/04 22:57:50 by anastasia-r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "./minishell.h"

/**
 * Custom structures
 */

// typedef enum e_token_type
// {
// 	COMMAND,
// 	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	REDIR_APPEND,
// 	HEREDOC,
// 	QUOTE,
// 	PATH,
// 	FLAG,
// 	ENV_VAR,
// 	EXIT,
// 	SPAC,
// 	SEPERATOR,
// 	COMMENT,
// 	ESCAPE,
// 	FIL
// } t_token_type;

/**
 * redirections should be NULL if there is no redirection
 */
typedef struct s_parsed t_parsed;

/**
 * see how declaration of the struct is done
 * in push swap
 *
 * also check for cleanups as this struct is malloced
 */
struct s_parsed
{
	// struct s_parsed *prev;
	char *command;
	char **args;
	char *redir_in;	 // keeps the name of redirection file
	char *redir_out; // keeps the name of redirection file
	int redir_flags;
	struct s_parsed *next;
	int pipe_fd[2]; // don't touch
	int pipe_in_fd; // file descriptor for input redirection
	int pipe_out_fd; // file descriptor for output redirection
	int pid1;
	int pid2;
	int arg_count; // number of arguments
	bool builtin; // is it a builtin command?
	bool pipe_input; // does this command has input from pipe
};


typedef struct s_split
{
	size_t i;
	size_t j;
	char *str; //string to be split
	int index; // used to track the current index in the string
	int flag; // used to track if we are inside a word
	int	quote_flag; // used to track if we are inside a quote
	int word_count; // word count ( number of tokens)
	char **splited; // The result of the splitting function ( Array of tokens)
} t_split;




typedef struct s_data
{
	char **env_copy;
	char **paths;
	char *input;	  // raw input
	char **inp_spltd; // input split by spaces & redirections & pipes
	int *spltd_type;
	t_parsed *parsed;
	t_parsed *parsed_head; // head of the parsed linked list
	t_split *split;
	int tkn_count;
	int pipes_count;
	int exit_status;
	int stdin_backup;
	int stdout_backup;
} t_data;

#endif
