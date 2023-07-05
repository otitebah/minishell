/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:48:28 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/24 18:21:28 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	split_args2_follow2(t_token *temp, t_args **args, int *y, int *z)
{
	int	x;

	*y = 0;
	*args = (*args)->next;
	x = 0;
	*z = 0;
	x = args_count(temp->next);
	(*args)->args = malloc(sizeof(char *) * (x + 1));
	(*args)->args[x] = NULL;
	(*z)++;
}

void	split_args2_follow(t_token *temp, t_args **args, int *y, int *z)
{
	int	x;

	x = 0;
	if (!*y && !*z)
	{
		x = args_count(temp);
		free ((*args)->args[0]);
		free ((*args)->args);
		(*args)->args = malloc(sizeof(char *) * (x + 1));
		(*args)->args[x] = NULL;
	}
}

void	split_args2_follow3(t_token *temp, t_args **args, int *y, int *z)
{
	if (temp->type == PIPE)
		split_args2_follow2(temp, args, y, z);
	else
	{
		split_args2_follow(temp, args, y, z);
		(*args)->args[(*y)++] = ft_strdup(temp->data);
	}
}

int	split_args2_follow4(t_token **temp, t_args **args, int *in, int *out)
{
	split_args3(*temp, args, in, out);
	*temp = (*temp)->next;
	return (0);
}

int	split_args2(t_token *temp, t_args **args, t_token *lst, t_env *env_parse)
{
	int	y;
	int	z;
	int	in;
	int	out;

	y = 0;
	z = 0;
	in = 0;
	out = 0;
	while (temp && *args)
	{
		if (temp->type == INPUT || temp->type == OUTPUT || temp->type == APPEND)
			split_args2_follow4(&temp, args, &in, &out);
		else if ((temp->type == CMD || temp->type == PIPE))
			split_args2_follow3(temp, args, &y, &z);
		else if (temp->type == DELIMITER)
		{
			in = 1;
			if (heredoc(*args, temp->data, env_parse, lst))
				return (1);
		}
		check_in_out(*args, in, out);
		temp = temp->next;
	}
	return (0);
}
