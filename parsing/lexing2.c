/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:49:46 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/23 04:38:20 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	lexing2_follow(char *line, t_token **lst, int *x, char *str)
{
	int		check;
	int		y;

	check = 0;
	y = *x;
	y += 2;
	while (line[y] == ' ' || line[y] == '\t')
		y++;
	while (line[y] && line[y] != '>' && line[y] != '<' && line[y] != '|')
	{
		if (line[y] == '"' || line[y] == '\'')
		{
			check = 1;
			break ;
		}
		y++;
	}
	str = malloc(sizeof(char) + 3);
	str[0] = line[*x];
	str[1] = line[*x + 1];
	str[2] = '\0';
	ft_lstadd_back(lst, ft_lstnew(str));
	free (str);
	return (check);
}

int	lexing2(char *line, t_token **lst, int *x)
{
	char	*str;
	int		check;

	str = NULL;
	if ((line[*x] == '<' && line[*x + 1] == '<')
		|| (line[*x] == '>' && line[*x + 1] == '>'))
	{
		check = lexing2_follow(line, lst, x, str);
		if (check)
			(*lst)->av_quotes = 1;
		(*x) += 2;
	}
	else if (line[*x] == '<' || line[*x] == '>')
	{
		str = malloc(sizeof(char) + 1);
		if (!str)
			exit (1);
		str[0] = line[*x];
		str[1] = '\0';
		ft_lstadd_back(lst, ft_lstnew(str));
		free (str);
		(*x)++;
	}
	return (0);
}
