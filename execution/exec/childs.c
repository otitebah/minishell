/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:51:47 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/24 15:55:42 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	child_builtins(t_args *tmp, t_pipe *pipes, t_data *lst)
{
	extern int	g_exit_status;

	if (tmp->infile == 1)
	{
		dup2(pipes->tmp, STDIN_FILENO);
		close(pipes->tmp);
	}
	if (tmp->outfile != 1)
		dup2(tmp->outfile, 1);
	else if (tmp->next)
		dup2(pipes->fd[1], 1);
	builtins(tmp, &lst->saving_env, &lst->saving_expo);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	g_exit_status = 0;
	exit(g_exit_status);
}

void	child_not_builtins(t_args *tmp, t_pipe *pipes)
{
	if (tmp->infile == 1)
	{
		dup2(pipes->tmp, STDIN_FILENO);
		close(pipes->tmp);
	}
	if (tmp->outfile != 1)
		dup2(tmp->outfile, 1);
	else if (tmp->next)
		dup2(pipes->fd[1], 1);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
}

void	child_process(t_args *tmp, t_pipe *pipes, t_data *lst, char **env)
{
	extern int	g_exit_status;

	if (tmp->infile != 0)
		dup2(tmp->infile, 0);
	if (pipe(pipes->fd) == -1)
	{
		perror("pipes failed");
		exit(1);
	}
	lst->pid[lst->id] = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);
	if (lst->pid[lst->id] == 0)
	{
		signal(SIGINT, handler3);
		if (check_if_builtins(tmp) == 1)
			child_builtins(tmp, pipes, lst);
		child_not_builtins(tmp, pipes);
		if (execute_cmd_pipe(tmp, lst->saving_expo, env) == 0)
		{
			g_exit_status = 127;
			exit(g_exit_status);
		}
	}
}

int	check_if_builtins(t_args *p)
{
	if (!ft_strcmp(p->args[0], "echo"))
		return (1);
	else if (!ft_strcmp(p->args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(p->args[0], "cd"))
		return (1);
	else if (!ft_strcmp(p->args[0], "env"))
		return (1);
	else if (!ft_strcmp(p->args[0], "export"))
		return (1);
	else if (!ft_strcmp(p->args[0], "unset"))
		return (1);
	else if (!ft_strcmp(p->args[0], "exit"))
		return (1);
	return (0);
}
