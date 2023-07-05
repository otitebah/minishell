/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:46:19 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/25 15:22:41 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lexing_follow3(t_token **temp)
{
	(*temp)->type = INPUT;
	(*temp)->next->type = INPUT;
	(*temp) = (*temp)->next;
}

void	lexing_follow2(t_token **temp)
{
	(*temp)->type = APPEND;
	(*temp)->next->type = APPEND;
	(*temp) = (*temp)->next;
}

void	lexing_follow(t_token **temp)
{
	(*temp)->type = HEREDOC;
	(*temp)->next->type = DELIMITER;
	(*temp) = (*temp)->next;
}

int	lexing3(t_token	**lst)
{
	t_token	*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->next && (!(ft_strncmp(temp->data, "<<", 2))))
			lexing_follow(&temp);
		else if (temp->next && (!(ft_strncmp(temp->data, ">>", 2))))
			lexing_follow2(&temp);
		else if (temp->next && (!(ft_strncmp(temp->data, "<", 1))))
			lexing_follow3(&temp);
		else if (temp->next && (!(ft_strncmp(temp->data, ">", 1))))
		{
			temp->type = OUTPUT;
			temp->next->type = OUTPUT;
			temp = temp->next;
		}
		else if ((!(ft_strncmp(temp->data, "|", 1))) && !temp->av_quotes)
			temp->type = PIPE;
		else
			temp->type = CMD;
		temp = temp->next;
	}
	return (0);
}

int	lexing(char *line, t_token **lst, int *x, t_env *env_parse)
{
	t_token	*temp;

	if (!(ft_strcmp(line, "\0")))
		return (1);
	while (line[*x] == ' ' || line[*x] == '\t')
		(*x)++;
	while (line[*x])
	{
		while (line[*x] && (line[*x] == ' ' || line[*x] == '\t'))
			(*x)++;
		if (check_quotes(lst, line, x, env_parse))
			return (1);
		lexing2(line, lst, x);
	}
	temp = *lst;
	while (temp)
	{
		if (temp->av_quotes != 1)
			temp->av_quotes = 0;
		temp = temp->next;
	}
	lexing3(lst);
	return (0);
}
