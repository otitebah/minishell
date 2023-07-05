/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:28:25 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/23 02:58:05 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	args_count(t_token *lst)
{
	int	count;

	count = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type != INPUT && lst->type != OUTPUT
			&& lst->type != APPEND && lst->type != HEREDOC
			&& lst->type != DELIMITER)
			count++;
		lst = lst->next;
	}
	return (count);
}
