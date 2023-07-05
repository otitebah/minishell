/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:09:11 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/24 20:59:49 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	split_args_follow(t_token *lst)
{
	int		max;
	t_token	*tmp;

	max = 0;
	tmp = lst;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->data, "<<")))
			max++;
		tmp = tmp->next;
	}
	return (max);
}

int	split_args(t_token *lst, t_args **args, t_env *env_parse)
{
	int			max;
	t_token		*temp;
	t_args		*temp2;
	extern int	g_exit_status;

	max = split_args_follow(lst);
	if (max >= 16)
	{
		write (2, "maximum here-document count exceeded\n", 38);
		g_exit_status = 2;
		exit (g_exit_status);
	}
	temp = lst;
	create_list(args, lst);
	(*args)->args = malloc(sizeof(char *));
	(*args)->args[0] = NULL;
	temp2 = *args;
	if (split_args2(temp, args, lst, env_parse))
		return (1);
	*args = temp2;
	return (0);
}
