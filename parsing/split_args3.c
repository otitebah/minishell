/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:53:36 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/25 15:52:09 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	split_args3_follow2(t_token *temp, t_args **args, int *in)
{
	(void)temp;
	(void)args;
	*in = 1;
}

void	split_args3_follow(t_token *temp, t_args **args, int *out)
{
	extern int	g_exit_status;

	*out = 1;
	if ((*args)->outfile == -1)
	{
		perror(temp->next->data);
		g_exit_status = 1;
	}
}

void	split_args3(t_token *temp, t_args **args, int *in, int *out)
{
	extern int	g_exit_status;

	if (temp->next && temp->type == INPUT)
	{
		(*args)->infile = open(temp->next->data, O_RDWR);
		split_args3_follow2(temp, args, in);
	}
	else if (temp->next && temp->type == OUTPUT)
	{
		if (!g_exit_status)
			(*args)->outfile = open(temp->next->data,
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		split_args3_follow(temp, args, out);
	}
	else if (temp->next && temp->type == APPEND)
	{
		if (!g_exit_status)
			(*args)->outfile = open(temp->next->data,
					O_RDWR | O_CREAT | O_APPEND, 0777);
		split_args3_follow(temp, args, out);
	}
}
