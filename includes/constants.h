/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasia-romanova <anastasia-romanova@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:44:07 by anastasia         #+#    #+#             */
/*   Updated: 2025/08/04 20:35:38 by anastasia-r      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define EXECNOTFOUND 127

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#ifndef FILE_ERR
#define FILE_ERR 1
#endif

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

#ifndef DONE
#define DONE true
#endif

#ifndef FAIL
#define FAIL false
#endif

#ifndef CHILD
#define CHILD 0
#endif

#ifndef PARENT
#define PARENT 1
#endif

#endif