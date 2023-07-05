/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:28:39 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/18 22:13:07 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list	*search_oldpwd(t_list *saving_env)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = saving_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "OLDPWD=", 7) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*search_pwd(t_list *saving_env)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = saving_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "PWD=", 4) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
