/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:26:45 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 13:58:52 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*search_path(t_list *saving_expo, char *node)
{
	t_list	*tmp;
	char	**spl;
	char	*spl_p;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node))) == 0)
		{
			spl = ft_split(tmp->value, '=');
			spl_p = ft_strdup(spl[1]);
			ft_free(spl);
			return (spl_p);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	search_home(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node) - 2)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	search_home_unset(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, node, (ft_strlen(node))) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	search_home2(t_list *saving_expo, char *node)
{
	t_list	*tmp;

	tmp = saving_expo;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, node) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	search_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (2);
		if (str[i] == '=' && !str[i + 1])
			return (3);
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
