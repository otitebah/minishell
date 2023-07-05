/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:22:04 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 19:06:12 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	env(t_args *p, t_list **saving_env, int i)
{
	t_list	*tmp;

	tmp = NULL;
	i = 1;
	if (p->infile == -1)
		return ;
	while (p->args[i])
	{
		if (p->args[i])
		{
			ft_error("env: ", p->args[i], "No such file or directory", 1);
			return ;
		}
		i++;
	}
	tmp = *saving_env;
	while (tmp)
	{
		ft_putendl_fd(tmp->value, p->outfile);
		tmp = tmp->next;
	}
}

int	builtins_utils(t_args *p, t_list **saving_env, t_list **saving_expo)
{
	char	filename[256];

	if (!ft_strcmp(p->args[0], "echo"))
	{
		echo(p->args, p);
		return (1);
	}
	else if (!ft_strcmp(p->args[0], "pwd"))
	{
		if (getcwd(filename, 256) != NULL)
			ft_putendl_fd(filename, p->outfile);
		return (1);
	}
	else if (!ft_strcmp(p->args[0], "cd"))
	{
		big_cd(saving_env, saving_expo, p);
		return (1);
	}
	return (0);
}

void	check_num(char *str)
{
	int			i;
	int			sign;
	extern int	g_exit_status;

	i = 0;
	sign = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			ft_putstr_fd("exit :", 1);
			ft_putstr_fd(str, 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			g_exit_status = 255 * sign;
			exit(g_exit_status);
		}
		i++;
	}
}

void	exit_func(char **str)
{
	extern int		g_exit_status;
	unsigned char	ex;

	if (str[0] && str[1] && str[2])
	{
		ft_putstr_fd("minishell : exit: to many arguments\n", 1);
		g_exit_status = 1;
		return ;
	}
	else if (str[1] && !str[2])
	{
		check_num(str[1]);
		ex = ft_atoi(str[1]);
		exit(ex);
	}
	else
	{
		g_exit_status = 1;
		exit(g_exit_status);
	}
}

void	builtins(t_args *p, t_list **saving_env, t_list **saving_expo)
{
	int			i;

	i = 1;
	if (!p->args[0])
		return ;
	if (builtins_utils(p, saving_env, saving_expo) == 1)
		;
	else if (!ft_strcmp(p->args[0], "env"))
		env(p, saving_env, i);
	else if (!ft_strcmp(p->args[0], "unset"))
	{
		if (p->infile == -1)
			return ;
		while (p->args[i])
		{
			unset_util(saving_env, saving_expo, p->args[i]);
			i++;
		}
	}
	else if (!ft_strcmp(p->args[0], "export"))
		export_a(saving_env, saving_expo, p);
	else if (!ft_strcmp(p->args[0], "exit"))
		exit_func(p->args);
}
