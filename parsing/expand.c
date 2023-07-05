/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:56 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/25 15:48:21 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expanded5(char *to_expand, char *str)
{
	extern int	g_exit_status;

	write (2, "$", 1);
	write (2, to_expand, ft_strlen(to_expand));
	write (2, ": ambiguous redirect\n", 22);
	free (to_expand);
	free (str);
	g_exit_status = 1;
}

int	expand4(char *line, int *y)
{
	int	j;

	j = 0;
	while (line[*y] && ((line[*y] >= 'a' && line[*y] <= 'z')
			|| (line[*y] >= 'A' && line[*y] <= 'Z')
			|| (line[*y] >= '0' && line[*y] <= '9')))
	{
		(*y)++;
		j++;
	}
	return (j);
}

int	expand3(t_token *lst)
{
	t_token	*temp;
	int		check1;

	check1 = 0;
	temp = lst;
	while (temp)
	{
		if ((!(ft_strcmp(temp->data, ">")) || (!(ft_strcmp(temp->data, ">>"))
					|| (!(ft_strcmp(temp->data, "<"))))))
		{
			check1++;
			break ;
		}
		temp = temp->next;
	}
	return (check1);
}

char	*expand2(char *to_expand, t_env *env_parse)
{
	char	*env_split;
	char	*expanded;
	int		i;

	env_split = NULL;
	expanded = NULL;
	while (env_parse)
	{
		i = 0;
		env_split = NULL;
		env_split = malloc(sizeof(char));
		env_split[0] = '\0';
		while (env_parse->value && env_parse->value[i] != '=')
			env_split = ft_chrjoin(env_split, env_parse->value[i++]);
		if (!(ft_strcmp(to_expand, env_split)))
		{
			expanded = ft_substr(env_parse->value, i + 1,
					ft_strlen(env_parse->value));
		}
		free (env_split);
		env_parse = env_parse->next;
	}
	return (expanded);
}

char	*expand(t_token *lst, char *line, int *x, t_env *env_parse)
{
	t_var2	var2;

	var2.expanded = 0;
	var2.check1 = 0;
	var2.check2 = 0;
	var2.check3 = 0;
	var2.p = 0;
	var2.y = 0;
	var2.i = 0;
	var2.check1 = expand3(lst);
	var2.str = malloc(sizeof(char));
	var2.str[0] = '\0';
	(*x)++;
	var2.y = *x;
	var2.j = expand4(line, &var2.y);
	var2.to_expand = ft_substr(line, *x, var2.j);
	var2.expanded = expand2(var2.to_expand, env_parse);
	if (var2.expanded)
		var2.check2++;
	expand6(&var2);
	if ((var2.check1 && !var2.check2) || (var2.check3 && var2.check1))
		return (expanded5(var2.to_expand, var2.str), free(var2.expanded), NULL);
	*x = var2.y;
	(free (var2.to_expand), free (var2.str));
	return (var2.expanded);
}
