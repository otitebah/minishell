/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:32:35 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/24 20:20:02 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	filenames_check(char *str)
{
	if ((!(ft_strcmp(str, "<"))) || (!(ft_strcmp(str, ">")))
		|| (!(ft_strcmp(str, "<<"))) || (!(ft_strcmp(str, "<<")))
		|| (!(ft_strncmp(str, "|", 1))) || (!(ft_strcmp(str, ";")))
		|| (!(ft_strcmp(str, "#"))))
		return (1);
	return (0);
}

int	errors_check4(t_token *lst)
{
	extern int	g_exit_status;

	if ((lst->next) && ((!(ft_strcmp(lst->data, "<")))
			|| (!(ft_strcmp(lst->data, "<<")))
			|| (!(ft_strcmp(lst->data, ">"))
				|| (!(ft_strcmp(lst->data, ">>"))))))
	{
		if (filenames_check(lst->next->data))
		{
			write (2, "syntax error near unexpected token `", 37);
			write (2, lst->next->data, 1);
			write (2, "\'\n", 2);
			g_exit_status = 258;
			return (g_exit_status);
		}
	}
	return (0);
}

int	error_check3(t_token *lst)
{
	extern int	g_exit_status;

	if (lst && (lst->next) && (lst->av_quotes != 1)
		&& (!(ft_strcmp(lst->data, "|"))))
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		g_exit_status = 258;
		return (g_exit_status);
	}
	return (0);
}

int	errors_check2(t_token *lst)
{
	extern int	g_exit_status;

	if ((!(lst->next)) && ((!(ft_strcmp(lst->data, "<")))
			|| (!(ft_strcmp(lst->data, "<<")))
			|| (!(ft_strcmp(lst->data, ">"))
				|| (!(ft_strcmp(lst->data, ">>"))))
			|| ((!(ft_strcmp(lst->data, "|"))) && !lst->av_quotes)))
	{
		write (2, "syntax error near unexpected token `newline'\n", 46);
		g_exit_status = 258;
		return (g_exit_status);
	}
	return (0);
}

int	errors_check(t_token *lst)
{
	extern int	g_exit_status;

	if (error_check3(lst))
		return (1);
	while (lst)
	{
		if (errors_check2(lst))
			return (1);
		if (errors_check4(lst))
			return (1);
		if ((lst->next) && (!(ft_strcmp(lst->data, "|")))
			&& (!(ft_strcmp(lst->next->data, "|"))))
		{
			write (2, "syntax error near unexpected token `|'\n", 39);
			g_exit_status = 258;
			return (g_exit_status);
		}
		lst = lst->next;
	}
	return (0);
}
