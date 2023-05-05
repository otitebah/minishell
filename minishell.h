/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:12:21 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/05 10:46:39 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>



typedef struct s_list {
    char *value;
    struct s_list *next;
    struct s_list *prev;
}   t_list;

typedef struct  s_data
{
   t_list **env;
   int exit_status;
} t_data;

char    *ft_strcpy(char *dest, char *src);
t_list  *get_env(char **env);

t_data g_data;

#endif