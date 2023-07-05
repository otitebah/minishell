/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:06:36 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 19:28:46 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	error_export(char **str, int i)
{
	if ((str[i][0] < 'a' || str[i][0] > 'z') && (str[i][0] < 'A'
			|| str[i][0] > 'Z'))
	{
		ft_error("minishell: ", str[i], "not a valid identifier", 1);
		return (0);
	}
	return (1);
}

void	equal_no_plus_utils(char **spl_p, t_list **saving_env, t_list *node,
		t_list *node2)
{
	char	*src;
	char	*res;

	src = ft_strjoin(spl_p[0], "=");
	if (spl_p[1])
	{
		res = ft_strjoin(src, spl_p[1]);
		free(node->value);
		node->value = ft_strdup(res);
		if (!node2)
			ft_lstadd_back3(saving_env, ft_lstnew3(ft_strdup(res)));
		else
		{
			free(node2->value);
			node2->value = ft_strdup(res);
		}
		free(res);
		free(src);
	}
}

void	equal_no_plus(t_list **saving_expo, t_list **saving_env, char *str)
{
	t_list	*node;
	t_list	*node2;
	char	**spl_p;

	spl_p = ft_split(str, '=');
	node = search_node1(*saving_expo, spl_p[0]);
	node2 = search_node(*saving_env, spl_p[0]);
	if (node)
		equal_no_plus_utils(spl_p, saving_env, node, node2);
	else
		(*saving_env) = export(str, &(*saving_env));
	(*saving_expo) = export(str, &(*saving_expo));
	ft_free(spl_p);
}

int	if_plus(t_list **saving_expo, t_list **saving_env, char *str)
{
	char	**spl_p;
	char	**remove_plus;
	char	*res;

	spl_p = ft_split(str, '+');
	if (!search_node_1(*saving_expo, spl_p[0]))
	{
		remove_plus = ft_split(str, '+');
		res = ft_strjoin(remove_plus[0], remove_plus[1]);
		(*saving_expo) = export(res, &(*saving_expo));
		(*saving_env) = export(res, &(*saving_env));
		ft_free(remove_plus);
		ft_free(spl_p);
		free(res);
		return (1);
	}
	ft_free(spl_p);
	return (0);
}
