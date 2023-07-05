/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:13:57 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 21:04:42 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	export_a_utils(t_list **saving_env, t_list **saving_expo, t_args *p,
		int i)
{
	char	**spl_p;

	if (search_plus(p->args[i]) == 0 && search_egal(p->args[i]) == 0
		&& !search_node(*saving_expo, p->args[i]))
		(*saving_expo) = export(p->args[i], &(*saving_expo));
	else if (search_egal(p->args[i]) == 3
		&& !search_path(*saving_expo, p->args[i]))
	{
		(*saving_env) = export(p->args[i], &(*saving_env));
		(*saving_expo) = export(p->args[i], &(*saving_expo));
	}
	else if (search_egal(p->args[i]) == 1 && search_plus(p->args[i]) == 0)
		equal_no_plus(saving_expo, saving_env, p->args[i]);
	else if (search_plus(p->args[i]) == 2)
	{
		spl_p = ft_split(p->args[i], '+');
		if (if_plus(saving_expo, saving_env, p->args[i]) == 1)
			;
		else if (search_node(*saving_expo, spl_p[0]))
		{
			if_plus2(saving_expo, p->args[i]);
			if_plus3(saving_env, p->args[i], spl_p[0]);
		}
		ft_free(spl_p);
	}
}

void	export_a(t_list **saving_env, t_list **saving_expo, t_args *p)
{
	int		i;
	t_list	*tmp1;

	i = 1;
	if (p->infile == -1)
		return ;
	if (p->args[i])
	{
		while (p->args[i])
		{
			if (error_export(p->args, i) == 0)
				return ;
			export_a_utils(saving_env, saving_expo, p, i);
			i++;
		}
	}
	else
	{
		tmp1 = (*saving_expo);
		if (*saving_expo)
			print_export(saving_expo);
		(*saving_expo) = tmp1;
	}
}

void	ft_error(char *entourage, char *input, char *error, int i)
{
	ft_putstr_fd(entourage, i);
	ft_putstr_fd(input, i);
	ft_putstr_fd(": ", i);
	ft_putendl_fd(error, i);
}

void	ft_free(char **str)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}
