/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 02:53:03 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/25 15:33:40 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expand6(t_var2 *var2)
{
	while (var2->expanded && var2->expanded[var2->p])
	{
		if (var2->expanded[var2->p] == ' ')
		{
			var2->check3++;
			break ;
		}
		var2->p++;
	}
}
