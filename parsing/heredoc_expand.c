/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:52:40 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/22 22:20:26 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	heredoc_expand3(char *line, int *j, int x)
{
	int	y;

	y = 0;
	*j = x;
	y = 0;
	while (line[*j] && ((line[*j] >= 'a' && line[*j] <= 'z')
			|| (line[*j] >= 'A' && line[*j] <= 'Z')
			|| (line[*j] >= '0' && line[*j] <= '9')))
	{
			(*j)++;
			y++;
	}
	return (y);
}

char	*heredoc_expand2(t_env *env_parse, char *to_expand)
{
	char	*str;
	char	*env_split;
	int		i;

	i = 0;
	str = NULL;
	env_split = NULL;
	env_split = malloc(sizeof(char));
	env_split[0] = '\0';
	while (env_parse->value && env_parse->value[i] != '=')
	{
		env_split = ft_chrjoin(env_split, env_parse->value[i]);
		i++;
	}
	if (!(ft_strcmp(to_expand, env_split)))
	{
		str = ft_substr(env_parse->value, i + 1,
				ft_strlen(env_parse->value));
	}
	free (env_split);
	return (str);
}

char	*heredoc_expand4(t_env *env_parse, char *to_expand, char *str2)
{
	t_env	*temp;

	temp = env_parse;
	while (env_parse)
	{
		str2 = heredoc_expand2(env_parse, to_expand);
		if (str2)
			break ;
		env_parse = env_parse->next;
	}
	env_parse = temp;
	return (str2);
}

char	*heredoc_expand5(char *str, char *str2, char *to_expand)
{
	if (str2)
		str = ft_join_free(str, str2);
	else
		free (str2);
	free (to_expand);
	return (str);
}

char	*heredoc_expand(char *line, t_env *env_parse, int x)
{
	char	*to_expand;
	int		y;
	int		j;
	char	*str;
	char	*str2;

	str = NULL;
	to_expand = NULL;
	x = 0;
	while (line[x])
	{
		if (line[x] == '$')
		{
			x++;
			y = heredoc_expand3(line, &j, x);
			to_expand = ft_substr(line, x, y);
			str2 = heredoc_expand4(env_parse, to_expand, str2);
			x = j - 1;
			str = heredoc_expand5(str, str2, to_expand);
		}
		else
			str = ft_chrjoin(str, line[x]);
		x++;
	}
	return (free (line), str);
}
