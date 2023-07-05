/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:14:18 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 16:38:21 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	handler3(int num)
{
	extern int	g_exit_status;

	(void)num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
	exit(g_exit_status);
}

void	child_exec_solo_cmd(t_args *p, t_list *saving_expo, char **env_copy,
		t_data *lst)
{
	extern int	g_exit_status;

	(void)lst;
	lst->pid[lst->id] = fork();
	signal(SIGINT, SIG_IGN);
	if (lst->pid[lst->id] == 0)
	{
		signal(SIGINT, handler3);
		signal(SIGQUIT, SIG_DFL);
		check_slash(p, env_copy);
		dup2(p->infile, 0);
		dup2(p->outfile, 1);
		if (p->infile != 0)
			close(p->infile);
		if (p->outfile != 1)
			close(p->outfile);
		if (execute_cmd(p, saving_expo, env_copy) == 0)
		{
			g_exit_status = 127;
			exit(g_exit_status);
		}
	}
	lst->id++;
}

void	while_solo_cmd(char **spl_path, char **env_copy, t_args *p, char *cmd)
{
	char	*command;
	int		i;

	i = 0;
	while (spl_path[i])
	{
		command = ft_strjoin(spl_path[i], cmd);
		if (access(command, X_OK) != -1)
			execve(command, (p)->args, env_copy);
		free(spl_path[i]);
		free(command);
		i++;
	}
}

int	execute_cmd(t_args *p, t_list *saving_expo, char **env_copy)
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
	spl_path = ft_split(find_path, ':');
	cmd = ft_strjoin("/", p->args[0]);
	if (p->args[0][0] == '.' || p->args[0][0] == '/')
		execve(p->args[0], (p)->args, env_copy);
	while_solo_cmd(spl_path, env_copy, p, cmd);
	ft_putstr_fd(*p->args, 2);
	write(2, ": command not found\n", 21);
	return (0);
}
