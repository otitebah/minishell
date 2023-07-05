/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_follow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:22:22 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/25 15:44:54 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_quotes_follow5(int *x, t_token **lst,
								t_env *env_parse, t_var *var)
{
	var->str2 = expand(*lst, var->line, x, env_parse);
	if (var->str2)
		var->str = ft_join_free(var->str, var->str2);
	else
		free (var->str2);
	(*x)--;
}

void	check_quotes_follow2(int *x, t_token **lst,
								t_env *env_parse, t_var *var)
{
	extern int	g_exit_status;

	(*x)++;
	while (var->line[*x] && var->line[*x] != '"')
	{
		if (var->line[*x] == '$' && !var->check)
		{
			var->str2 = expand(*lst, var->line, x, env_parse);
			if (var->str2)
				var->str = ft_join_free(var->str, var->str2);
			else
				free (var->str2);
		}
		if (var->line[*x] != '"' && var->line[*x] != '$')
		{
			if (var->line[*x] == '|')
				var->quotes_check++;
			var->str = ft_chrjoin(var->str, var->line[*x]);
		}
		else
			(*x)--;
		(*x)++;
	}
}

int	check_quotes_follow4(int *x, t_token **lst, t_env *env_parse, t_var *var)
{
	extern int	g_exit_status;

	check_quotes_follow2(x, lst, env_parse, var);
	if (var->line[*x] != '"')
	{
		write(2, "syntax error near unexpected token`unclosed quote'\n", 52);
		g_exit_status = 258;
		return (free (var->str), g_exit_status);
	}
	else if (var->line[*x] == '"' && var->line[*x + 1] == '\0' && var->str)
	{
		ft_lstadd_back(lst, ft_lstnew(var->str));
		check_quotes5(var, *lst, var->str);
		var->lock++;
	}
	return (0);
}

int	check_quotes_follow(char *line, int *x, t_token **lst)
{
	int	a;
	int	check;

	a = 0;
	check = 0;
	while (line[a])
	{
		if (line[a] == '<' && line[a + 1] == '<')
		{
			check++;
			break ;
		}
		a++;
	}
	if (line[*x] == '|')
	{
		ft_lstadd_back(lst, ft_lstnew("|"));
		(*x)++;
	}
	return (check);
}

int	check_quotes_follow6(int *x, t_token **lst, t_env *env_parse, t_var *var)
{
	extern int	g_exit_status;

	if (var->line[0] == '/' && var->line[1] == '\0')
		return (write (2, "/: is a directory\n", 18), free (var->str), 1);
	else if (var->line[*x] == '$' && var->line[*x + 1] == '?')
	{
		var->str = ft_join_free(var->str, ft_itoa(g_exit_status));
		(*x)++;
	}
	else if (var->line[*x] == '"')
	{
		if (check_quotes_follow4(x, lst, env_parse, var))
			return (1);
	}
	else if (var->line[*x] == '\'')
	{
		var->str = check_quotes4(lst, var, x, var->str);
		if (!var->str)
			return (1);
	}
	else if (var->line[*x] == '$' && !var->check)
		check_quotes_follow5(x, lst, env_parse, var);
	else
		var->str = ft_chrjoin(var->str, var->line[*x]);
	return (0);
}
