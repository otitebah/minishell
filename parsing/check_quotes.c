/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:31 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/25 15:53:01 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_quotes5(t_var *var, t_token *lst, char *str)
{
	t_token	*temp;
	int		check;
	int		x;

	check = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '|' && var->quotes_check)
		{
			temp = lst;
			while (temp)
			{
				if (!temp->next)
					temp->av_quotes = 1;
				temp = temp->next;
			}
		}
		x++;
	}
}

char	*check_quotes4(t_token **lst, t_var *var, int *x, char *str)
{
	extern int	g_exit_status;

	(*x)++;
	while (var->line[*x] && var->line[*x] != '\'')
	{
		if (var->line[*x] == '|')
			var->quotes_check++;
		str = ft_chrjoin(str, var->line[*x]);
		(*x)++;
	}
	if (var->line[*x] != '\'')
	{
		write(2, "syntax error near unexpected token`unclosed quote'\n", 52);
		g_exit_status = 258;
		return (free (var->str), NULL);
	}
	else if (var->line[*x] == '\'' && str && var->line[*x + 1] == '\0')
	{
		ft_lstadd_back(lst, ft_lstnew(str));
		check_quotes5(var, *lst, str);
		var->lock++;
	}
	return (str);
}

void	check_quotes3(t_env *env_parse, char *str)
{
	char	*str2;
	int		x;

	x = 0;
	str2 = heredoc_expand(ft_strdup("$HOME"), env_parse, x);
	write(2, str2, ft_strlen(str2));
	write (2, ": is a directory\n", 18);
	free (str);
	free (str2);
}

char	*check_quotes2(char *line, int *x, t_token **lst, t_env *env_parse)
{
	char	*str;
	char	*str2;

	(*x)++;
	while (line[*x] && line[*x] != '"')
	{
		if (line[*x] == '$')
		{
			str2 = expand(*lst, line, x, env_parse);
			if (str2)
			{
				free (str);
				str = ft_strjoin(str, str2);
				free (str2);
			}
			else
				free (str2);
		}
		if (line[*x] != '"')
			str = ft_chrjoin(str, line[*x]);
		else
			(*x)--;
		(*x)++;
	}
	return (str);
}

int	check_quotes(t_token **lst, char *line, int *x, t_env *env_parse)
{
	t_var		var;
	extern int	g_exit_status;

	var.lock = 0;
	var.quotes_check = 0;
	var.str = ft_strdup("");
	var.line = line;
	var.check = check_quotes_follow(line, x, lst);
	while (line[*x] && line[*x] != ' ' && line[*x] != '|'
		&& line[*x] != '<' && line[*x] != '>')
	{
		if (check_quotes_follow6(x, lst, env_parse, &var))
			return (1);
		(*x)++;
	}
	if (var.str[0] && !var.lock)
	{
		ft_lstadd_back(lst, ft_lstnew(var.str));
		check_quotes5(&var, *lst, var.str);
	}
	return (free (var.str), 0);
}
