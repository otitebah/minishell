/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:12:53 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/22 17:08:33 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*sort_list(t_list **saving_expo)
{
	t_list	*tmp;
	char	*swap;

	tmp = (*saving_expo);
	while ((*saving_expo)->next != NULL)
	{
		if (ft_strncmp((*saving_expo)->value,
				(*saving_expo)->next->value, 1) > 0)
		{
			swap = (*saving_expo)->value;
			(*saving_expo)->value = (*saving_expo)->next->value;
			(*saving_expo)->next->value = swap;
			(*saving_expo) = tmp;
		}
		else
			(*saving_expo) = (*saving_expo)->next;
	}
	(*saving_expo) = tmp;
	return (*saving_expo);
}

t_list	*export(char *p, t_list **saving_expo)
{
	t_list	*new;
	t_list	*res;

	if (search_home2(*saving_expo, p) == 0)
	{
		new = create_node(p);
		ft_lstadd_back3(saving_expo, new);
		res = sort_list(saving_expo);
	}
	else
		res = sort_list(saving_expo);
	return (res);
}

void	*env_if_egal(char *p, t_list **saving_env)
{
	t_list	*new;

	new = NULL;
	new = create_node(p);
	ft_lstadd_back3(saving_env, new);
	return (0);
}
