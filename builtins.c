/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:23:27 by otitebah          #+#    #+#             */
/*   Updated: 2023/05/05 11:12:45 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **p)
{
	int	i;
	
	i = 1;
	while (p[i])
	{
		while (!ft_strcmp(p[i], "-n"))
			i++;
		printf ("%s ", p[i]);
		i++;
	}
	if (ft_strcmp(p[1], "-n"))
		printf("\n");
}

void	cd(char **p)
{
	if (!ft_strcmp(p[1], "~"))
		chdir(getenv("HOME"));
	else if (chdir(p[1]))
		perror("minishell: cd");
}



int main(int ac, char **av, char **env)
{
	(void)	ac;
	(void)	av;
	(void)	env;
    char	*line;
    char	**p;
	t_list	*saving_env;
	t_list	*data;

	data = (t_list *)malloc(sizeof(t_list));
	saving_env = get_env(env);
	
    while (1)
    {
        line = readline("minishell$ ");
		p = ft_split(line, ' ');
		if (!ft_strcmp(p[0], "echo"))
			echo(p);
		if (!ft_strcmp(p[0], "pwd"))
		{
			char filename[256];
			getcwd(filename, 256);
			printf("%s\n", filename);
		}
		if (!ft_strcmp(p[0] , "exit"))
			exit(0);
		if (!ft_strcmp(p[0], "env"))
		{
			while (saving_env)
			{
				printf("%s\n", saving_env->value);
				saving_env = saving_env->next;
			}
		}
		if (!ft_strcmp(p[0], "cd"))
			cd(p);
		if (!ft_strcmp(p[0], "unset"))
		{
			if (!ft_strcmp(p[1], saving_env->value))
		}
	}
}