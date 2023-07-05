/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:55:43 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/24 20:15:41 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	check_slash(t_args *p, char **env)
{
	extern int	g_exit_status;

	if (p->args[0][0] == '/')
	{
		execve(p->args[0], p->args, env);
		ft_putstr_fd(*p->args, 2);
		write(2, ": command not founddd\n", 23);
		g_exit_status = 127;
		exit(g_exit_status);
	}
}

void	free_execut_pipe(t_args *p, char *cmd, char **spl_path)
{
	free(cmd);
	ft_free(spl_path);
	ft_putstr_fd(*p->args, 2);
	write(2, ": command not found\n", 20);
}

int	search_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '+' && str[i + 1] == '=' && !str[i + 2])
			|| (str[i] == '+' && str[i + 1] == '=' && str[i + 2]))
		{
			if (str[i] == '+' && str[i + 1] == '=' && str[i + 2])
				return (2);
			else if (str[i] == '+' && str[i + 1] == '=' && !str[i + 2])
				return (1);
		}
		i++;
	}
	return (0);
}

void	nosushfile(void)
{
	extern int	g_exit_status;

	perror("");
	g_exit_status = 1;
}
