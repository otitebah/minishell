/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:27:48 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/23 03:05:10 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	check_n(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (2);
}

int	if_echo(char **p, int i, t_args *out)
{
	if (check_n(p[i]) == 1)
	{
		while (p[i])
		{
			ft_putstr_fd(p[i++], out->outfile);
			if (p[i])
				ft_putstr_fd(" ", out->outfile);
		}
		if (check_n(p[1]) == 1 || check_n(p[1]) == 2)
			ft_putstr_fd("\n", out->outfile);
		return (0);
	}
	else if (check_n(p[i]) == 2)
	{
		while (p[i])
		{
			ft_putstr_fd(p[i++], out->outfile);
			if (p[i])
				ft_putstr_fd (" ", out->outfile);
		}
		if (check_n(p[1]) == 1 || check_n(p[1]) == 2)
			ft_putstr_fd ("\n", out->outfile);
		return (0);
	}
	return (1);
}

void	echo(char **p, t_args *out)
{
	int	i;

	i = 1;
	if (out->infile == -1)
		return ;
	if (p[i] == NULL)
	{
		ft_putstr_fd("\n", out->outfile);
		return ;
	}
	while (p[i])
	{
		if (if_echo(p, i, out) == 0)
			return ;
		i++;
	}
}
