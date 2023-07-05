/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:17:49 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/22 23:37:43 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	l_free(char *final, char **old_value, char **spl_p, char **spl)
{
	free(final);
	ft_free(old_value);
	ft_free(spl_p);
	ft_free(spl);
}

char	*if_plus2_utils(t_list *node, char **spl)
{
	char	*res;
	char	*final;

	res = ft_strjoin(node->value, "=");
	final = ft_strjoin(res, spl[1]);
	free(res);
	return (final);
}

void	if_plus2(t_list **saving_expo, char *str)
{
	t_list		*node;
	char		*res;
	char		*final;
	char		*add_egal;
	t_helper	*help;

	help = malloc(sizeof(t_helper));
	help->spl_p = ft_split(str, '+');
	help->spl = ft_split(str, '=');
	node = search_node(*saving_expo, help->spl_p[0]);
	help->old_value = ft_split(node->value, '=');
	add_egal = ft_strjoin(help->old_value[0], "=");
	if (help->old_value[1])
	{
		res = ft_strjoin(add_egal, help->old_value[1]);
		free(add_egal);
		final = ft_strjoin(res, help->spl[1]);
		free(res);
	}
	else
		final = if_plus2_utils(node, help->spl);
	free(node->value);
	node->value = ft_strdup(final);
	l_free(final, help->old_value, help->spl_p, help->spl);
	free(help);
}

void	if_plus3_utils(t_list *node2, char **spl_p, char **spl,
		char **old_value)
{
	char	*add_equal;
	char	*res;
	char	*final;

	add_equal = ft_strjoin(spl_p[0], "=");
	res = ft_strjoin(add_equal, old_value[1]);
	free(add_equal);
	final = ft_strjoin(res, spl[1]);
	free(res);
	free(node2->value);
	node2->value = ft_strdup(final);
	free(final);
}

void	if_plus3(t_list **saving_env, char *str, char *spl_p)
{
	char	**spl;
	t_list	*node2;
	char	*final;
	char	**old_value;

	final = NULL;
	spl = ft_split(str, '=');
	node2 = search_node1(*saving_env, spl[0]);
	if (search_node1(*saving_env, spl[0]))
	{
		old_value = ft_split(node2->value, '=');
		if (old_value[1])
			if_plus3_utils(node2, &spl_p, spl, old_value);
		else
		{
			final = ft_strjoin(node2->value, spl[1]);
			free(node2->value);
			node2->value = ft_strdup(final);
			free(final);
		}
		ft_free(old_value);
	}
	ft_free(spl);
}
