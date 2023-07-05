/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:28:35 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/23 02:58:38 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_in_out(t_args *args, int in, int out)
{
	if (!in)
		args->infile = 0;
	if (!out)
		args->outfile = 1;
}
