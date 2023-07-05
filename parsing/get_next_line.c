/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:03:53 by machaiba          #+#    #+#             */
/*   Updated: 2023/05/16 20:08:37 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check(char *b)
{
	int	x;

	x = 0;
	while (b[x])
	{
		if (b[x] == '\n')
			return (1);
		x++;
	}
	return (0);
}

char	*get_read(int fd, char *reserve)
{
	char		*buff;
	int			x;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	buff[0] = '\0';
	while (!check(buff))
	{
		x = read(fd, buff, BUFFER_SIZE);
		if (x == -1)
			return (free (buff), free (reserve), NULL);
		buff[x] = '\0';
		if (!x)
		{
			free (buff);
			return (reserve);
		}
		reserve = ft_strjoin(reserve, buff);
	}
	free(buff);
	return (reserve);
}

char	*get_line1(char *line, char *reserve)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (reserve && reserve[x] && reserve[x] != '\n')
		x++;
	if (reserve && reserve[x] == '\n')
		x++;
	line = malloc(sizeof(char) * (x + 1));
	y = x;
	x = 0;
	while (x < y && reserve && reserve[x])
	{
		line[x] = reserve[x];
		x++;
	}
	line[x] = '\0';
	return (line);
}

char	*get_reserve(char *reserve)
{
	char	*reserve1;

	reserve1 = ft_strdup(ft_strchr(reserve, '\n'));
	free (reserve);
	return (reserve1);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve = get_read(fd, reserve);
	line = get_line1(line, reserve);
	if (line[0] == '\0')
	{
		free (reserve);
		reserve = NULL;
		free (line);
		return (NULL);
	}
	reserve = get_reserve(reserve);
	return (line);
}
