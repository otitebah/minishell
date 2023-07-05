/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:51:02 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 15:19:07 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	norm(t_list **head, t_list *cur)
{
	(*head) = cur->next;
	free(cur->value);
	free(cur);
}

void	unset(t_list **head, char *key)
{
	t_list	*cur;
	t_list	*prev;

	cur = (*head);
	prev = NULL;
	while (cur && cur->next != NULL && ft_strncmp(cur->value, key,
			ft_strlen(key)))
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev == NULL && cur)
	{
		(*head) = cur->next;
		free(cur->value);
		free(cur);
	}
	else if (cur && prev && ft_strncmp(cur->value, key, ft_strlen(key)) == 0)
	{
		prev->next = cur->next;
		free(cur->value);
		free(cur);
	}
}

void	unset_util(t_list **saving_env, t_list **saving_expo, char *str)
{
	if (search_home_unset(*saving_expo, str))
		unset(saving_expo, str);
	if (search_home_unset(*saving_env, str))
		unset(saving_env, str);
}
