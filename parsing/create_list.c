/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:28:30 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/16 20:07:36 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	create_list(t_args **args, t_token *token)
{
	ft_lstadd_back2(args, ft_lstnew2());
	while (token)
	{
		if (token->type == PIPE)
			ft_lstadd_back2(args, ft_lstnew2());
		token = token->next;
	}
	return (0);
}
