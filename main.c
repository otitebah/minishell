/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:13:26 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 15:41:41 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

void	ft_execution(t_global *global, t_data *list, t_pipe *pipes, t_args *p)
{
	(void)p;
	global->env_copy = get_env_copy(list->saving_env);
	implement_cmnd(list, global->args, global->env_copy, pipes);
	global->tmp = global->args;
	while (global->args->next)
	{
		close(pipes->fd[0]);
		close(pipes->fd[1]);
		global->args = global->args->next;
	}
	global->args = global->tmp;
	waitpid(list->pid[pipes->cmds - 1], &g_exit_status, 0);
	while (wait(0) != -1)
		;
	if (WIFSIGNALED(g_exit_status) == 1 && g_exit_status != 1)
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	else if (g_exit_status != 1)
		g_exit_status = WEXITSTATUS(g_exit_status);
	dup2(pipes->tmp, global->stdin_main);
	free(list->pid);
	ft_free(global->env_copy);
}

void	initialization(t_global *global, char **env, t_data *list,
		t_pipe *pipes)
{
	global->stdin_main = dup(0);
	list->saving_env = get_env(env);
	list->saving_expo = get_expo(env);
	pipes->cmds = 0;
	pipes->tmp = dup(0);
	global->env_parse = (t_env *)list->saving_env;
	global->lst = NULL;
	global->args = NULL;
	global->env_copy = NULL;
}

void	initia_exec(t_global *global)
{
	global->lst = NULL;
	global->args = NULL;
	global->x = 0;
	global->line = readline("minishell:$> ");
}

int	main(int ac, char **av, char **env)
{
	t_global	global;
	t_data		*list;
	t_pipe		*pipes;

	(void)av;
	(void)ac;
	list = malloc(sizeof(t_data));
	pipes = malloc(sizeof(t_pipe));
	initialization(&global, env, list, pipes);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		initia_exec(&global);
		if (!global.line)
			(printf("exit\n"), exit(0));
		add_history(global.line);
		if (!(lexing(global.line, &global.lst, &global.x, global.env_parse))
			&& (!(errors_check(global.lst)) && (!(split_args(global.lst,
							&global.args, global.env_parse)))))
			ft_execution(&global, list, pipes, global.args);
		(free(global.line), free_parser(global.args, global.lst));
	}
}
