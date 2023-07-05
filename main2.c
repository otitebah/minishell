/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 05:01:40 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 16:38:28 by machaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int num)
{
	extern int	g_exit_status;

	g_exit_status = 1;
	(void) num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	**get_env_copy(t_list *saving_env)
{
	t_list	*tmp;
	char	**env_copy;
	int		i;

	tmp = saving_env;
	i = 0;
	while (saving_env)
	{
		i++;
		saving_env = saving_env->next;
	}
	saving_env = tmp;
	env_copy = malloc(sizeof(char *) * (i + 1));
	env_copy[i] = NULL;
	i = 0;
	while (saving_env)
	{
		env_copy[i] = ft_strdup(saving_env->value);
		i++;
		saving_env = saving_env->next;
	}
	saving_env = tmp;
	return (env_copy);
}

void	free_parser2(t_token *lst)
{
	t_token	*lst_temp;

	if (lst)
	{
		while (lst)
		{
			lst_temp = lst;
			lst = lst->next;
			free(lst_temp->data);
			free(lst_temp);
		}
	}
}

void	free_parser(t_args *args, t_token *lst)
{
	int		y;
	t_args	*args_temp;

	if (args && args->args)
	{
		while (args)
		{
			y = 0;
			while (args->args[y])
			{
				free(args->args[y]);
				y++;
			}
			free(args->args);
			args_temp = args;
			args = args->next;
			free(args_temp);
		}
	}
	free_parser2(lst);
}
