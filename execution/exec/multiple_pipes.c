/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:17:05 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/24 23:17:40 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	while_pipe(char **spl_path, char *cmd, t_args *p, char **env)
{
	int		i;
	char	*command;

	i = 0;
	while (spl_path[i])
	{
		command = ft_strjoin(spl_path[i], cmd);
		if (access(command, X_OK) != -1)
		{
			free(cmd);
			ft_free(spl_path);
			execve(command, (p)->args, env);
		}
		free(command);
		i++;
	}
}

int	execute_cmd_pipe(t_args *p, t_list *saving_expo, char **env)
{
	char	**spl_path;
	char	*cmd;
	char	*find_path;

	find_path = search_path(saving_expo, "PATH");
	if (!find_path)
	{
		ft_putstr_fd(*p->args, 2);
		write(2, ": command not found\n", 21);
		return (0);
	}
	check_slash(p, env);
	spl_path = ft_split(find_path, ':');
	free(find_path);
	cmd = ft_strjoin("/", p->args[0]);
	if (p->args[0][0] == '.' || p->args[0][0] == '/')
		execve(p->args[0], (p)->args, env);
	while_pipe(spl_path, cmd, p, env);
	free_execut_pipe(p, cmd, spl_path);
	return (0);
}

void	no_pipe(char **str, char **env_copy, t_data *lst, t_args *p)
{
	if (!str[0])
		return ;
	if (check_if_builtins(p) == 1)
		builtins(p, &lst->saving_env, &lst->saving_expo);
	else
	{
		child_exec_solo_cmd(p, lst->saving_expo, env_copy, lst);
		lst->id++;
	}
}

void	while_implement(t_pipe *pipes, t_data *lst, char **env_copy, t_args *p)
{
	int			i;
	extern int	g_exit_status;

	i = 0;
	while (p && i < pipes->cmds)
	{
		g_exit_status = 0;
		if (!p->args[0])
		{
			if (p->infile == -1)
				perror("");
			i++;
		}
		else
		{
			child_process(p, pipes, lst, env_copy);
			lst->id++;
			dup2(pipes->fd[0], 0);
			close(pipes->fd[1]);
			close(pipes->fd[0]);
			i++;
		}
		p = p->next;
	}
}

void	implement_cmnd(t_data *lst, t_args *p, char **env_copy, t_pipe *pipes)
{
	t_args		*tmp;
	extern int	g_exit_status;

	pipes->cmds = 0;
	tmp = p;
	while (tmp)
	{
		tmp = tmp->next;
		pipes->cmds++;
	}
	tmp = p;
	lst->id = 0;
	lst->pid = malloc(sizeof(int) * pipes->cmds);
	if (pipes->cmds == 1 && p->infile != -1)
		no_pipe(p->args, env_copy, lst, p);
	else if (pipes->cmds != 1)
	{
		while_implement(pipes, lst, env_copy, p);
		p = tmp;
		close(0);
		dup2(pipes->tmp, 0);
	}
	else if (pipes->cmds == 1 && p->infile == -1)
		nosushfile();
}
