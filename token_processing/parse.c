/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:14:47 by relgheit          #+#    #+#             */
/*   Updated: 2025/08/04 17:21:49 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// skips whatever insided the quotes and increments the index
static void skip(t_split *split, int *i)
{
    char quote;
    
    quote = split->str[*i];
    (*i)++;
    while (split->str[*i] != '\0' && split->str[*i] != quote)
        (*i)++;
    if (split->str[*i] == quote)
        (*i)++;
    if (split->flag == 1)
        split->flag = 0;
}

// counts the number of Tokens in string
void count_word(t_split *split)
{
    int i = 0;
    split->word_count = 0;
    split->flag = 0;
    split->word_count = 0;
    split->flag = 0;
    
    while (split->str[i])
    {
        if (ft_isquote(split->str[i]))
        {
            split->word_count++;
            skip(split, &i);
            split->flag = 0;  // Reset flag after quoted string
            continue;
        }
        else if (ft_isalnum(split->str[i]) && split->flag == 0)
        {
            split->flag = 1;
            split->word_count++;
        }
        else if (ft_isspace(split->str[i]))
            split->flag = 0;
        else if (ft_ismeta(split->str[i]))
        {
            if ((split->str[i] == '>' || split->str[i] == '<')
                && split->str[i + 1] == split->str[i])
                i++;
            split->word_count++;
            split->flag = 0;
        }
        i++;
    }
}

// Extracts the word from the string based on the start and finish indices
char *word_dup(char *str, int start, int finish)
{
    char *word;
    int i = 0;
    
    word = malloc((finish - start + 1) * sizeof(char));
    if (!word)
        return (NULL);
    while (start < finish)
        word[i++] = str[start++];
    word[i] = '\0';
    return (word);
}
//// handles quotes in the string and returns the word inside the quotes
// including the quotes themselves

static char *handle_quotes(char *s, int *i)
{
    int start = *i;
    char quote_char = s[*i];
    
    if (ft_isquote(quote_char)) {
        (*i)++;
        while (s[*i] && s[*i] != quote_char)
            (*i)++;
        if (s[*i] == quote_char)
            (*i)++;
        return (word_dup(s, start, *i));
    }
    return (NULL);
}

// handles all cases of redirections and returns them as a word
static char	*handle_redirections(char *s, int *i)
{
    int start;
	char *word;
    
    start = *i;
    if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
    {
        (*i) ++;
        word = word_dup(s, start, start + 2);
    }
    else
    {
        // (*i)++;
        word = word_dup(s, start, start + 1);
    }
	if (!word)
		return (NULL);
	return (word);
}

// splits the string into words based on spaces, quotes, and redirections and pipes
void split_s(t_split *split)
{
    size_t i = 0;
    size_t j = 0;
    char *special_word;
	split->index = -1;
    
    while (i <= ft_strlen(split->str))
    {
        special_word = handle_quotes(split->str, (int *)&i);
        if (special_word)
        {
            if (split->index >= 0)
                split->splited[j++] = word_dup(split->str, split->index, i - ft_strlen(special_word));
            split->splited[j++] = special_word;
            split->index = -1;
            continue;
        }
        if ((ft_isspace(split->str[i]) || i == ft_strlen(split->str)) && split->index >= 0)
        {
            split->splited[j++] = word_dup(split->str, split->index, i);
            split->index = -1;
        }
        else if ((split->str[i] == '<' || split->str[i] == '>'))
		{
			if (split->index >= 0)
            {
                split->splited[j++] = word_dup(split->str, split->index, i);
                split->index = -1;
            }
			split->splited[j++] = handle_redirections(split->str, (int *)&i);
			split->index = -1;
		}
        else if (ft_ismeta(split->str[i]))
        {
            if (split->index >= 0)
                split->splited[j++] = word_dup(split->str, split->index, i);
            split->splited[j++] = word_dup(split->str, i, i + 1);
            split->index = -1;
        }
        else if (!ft_isspace(split->str[i]) && split->index < 0)
            split->index = i;
        i++;
        free(special_word); 
    }
    split->splited[j] = NULL;
}

static void init_split(t_split *split)
{
    split->i = 0;
    split->j = 0;
    split->index = -1;
    split->flag = 0;
    split->quote_flag = 0;
    split->word_count = 0;
    split->splited = NULL;
    split->str = NULL;
}
static void free_split(t_split **split)
{
    int k;
    
    if (!(*split))
        return;
    k = 0;
    if ((*split)->splited)
    {
        while ((*split)->splited[k])
        {
            free((*split)->splited[k]);
            (*split)->splited[k] = NULL;
            k++;
        }
        free((*split)->splited);
        (*split)->splited = NULL;
    }
    if ((*split)->str)
        free((*split)->str);
    free((*split));
    (*split) = NULL;
    return;
}
void ft_split_token(t_data *data)
{
	t_split *split;
	
	split = malloc(sizeof(t_split));
	if (!split)
		return;
    init_split(split);
	split->str = ft_strdup(data->input);
	count_word(split);
	split->splited = malloc((split->word_count + 1) * sizeof(char *));
    data->inp_spltd = malloc((split->word_count + 1) * sizeof(char *));
	if (!split->splited || !data->inp_spltd)
	{
        if (split->str)
            free(split->str);
        if (split)
            ft_free_ptr_array(split->splited);
        if (data->inp_spltd)
            ft_free_ptr_array(data->inp_spltd);
		return ;
	}
	split_s(split);
    split->j = 0;
    while (split->splited[split->j])
    {
        data->inp_spltd[split->j] = ft_strdup(split->splited[split->j]);
        split->j++;
    }
    data->inp_spltd[split->j] = NULL;
    free(data->input);
    data->input = NULL;
    if (split)
		free_split(&split);
	return ;
}
