/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:37:23 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/15 10:35:43 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_args	*ft_lstnew2(void)
{
	t_args	*head;

	head = NULL;
	head = malloc(sizeof(t_args));
	head->next = NULL;
	return (head);
}

t_token	*ft_lstnew(char *data)
{
	t_token	*head;

	head = NULL;
	head = malloc(sizeof(t_token));
	head->data = ft_strdup(data);
	head->next = NULL;
	return (head);
}
