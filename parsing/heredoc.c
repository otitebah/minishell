/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:45:22 by machaiba          #+#    #+#             */
/*   Updated: 2023/06/24 18:26:20 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handler2(int num)
{
	(void) num;
	printf("\n");
	exit (10);
}

int	heredoc3(int id, int fd[2])
{
	int			status;
	extern int	g_exit_status;

	status = 0;
	waitpid(id, &status, 0);
	if (WEXITSTATUS(status) == 10)
	{
		close (fd[1]);
		g_exit_status = 1;
		return (g_exit_status);
	}
	else if (WEXITSTATUS(status) == 20)
	{
		close (fd[1]);
		g_exit_status = 0;
		return (g_exit_status);
	}
	close (fd[1]);
	return (0);
}

void	heredoc2(char *line, t_env *env_parse, int fd[2])
{
	char	*str;
	int		x;

	str = NULL;
	x = 0;
	str = heredoc_expand(line, env_parse, x);
	write(fd[1], str, ft_strlen(str));
	write (fd[1], "\n", 1);
	free (str);
}

void	heredoc4(t_args *args, int fd[2])
{
	if (args->infile != -1)
		args->infile = fd[0];
	args->outfile = 1;
}

int	heredoc(t_args *args, char *delimiter, t_env *env_parse, t_token *lst)
{
	char	*line;
	int		fd[2];
	int		id;

	(pipe(fd), signal(SIGINT, SIG_IGN));
	heredoc4(args, fd);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, handler2);
		while (1)
		{
			line = readline("> ");
			if (line && line[0] == '\n')
				continue ;
			else if (!line || (!(ft_strcmp(line, delimiter))))
				(free (line), close (fd[1]), exit (20));
			else if (lst && (!(lst->av_quotes)))
				heredoc2(line, env_parse, fd);
			else
				(write(fd[1], line, ft_strlen(line)), write (fd[1], "\n", 1));
		}
	}
	return (heredoc3(id, fd));
}
