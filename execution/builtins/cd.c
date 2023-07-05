/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:58:03 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/24 04:20:42 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	modify_pwd(t_list **saving_env, char *new_pwd)
{
	t_list	*pwd_found;

	pwd_found = search_pwd(*saving_env);
	if (pwd_found)
	{
		free(pwd_found->value);
		pwd_found->value = ft_strjoin("PWD=", new_pwd);
	}
}

void	add_oldpwd(t_list **saving_env, char *old_pwd)
{
	t_list	*new;
	char	*str;
	char	*new_str;
	t_list	*oldpwd_found;

	oldpwd_found = NULL;
	new_str = NULL;
	new = NULL;
	str = "OLDPWD=";
	oldpwd_found = search_oldpwd(*saving_env);
	if (oldpwd_found != NULL)
	{
		free(oldpwd_found->value);
		oldpwd_found->value = ft_strjoin("OLDPWD=", old_pwd);
	}
	else
	{
		new = (t_list *)malloc(sizeof(t_list));
		new_str = ft_strjoin(str, old_pwd);
		new->value = ft_strdup(new_str);
		new->next = NULL;
		ft_lstadd_front(saving_env, new);
		free(new_str);
	}
}

int	cd(char **p, t_list *saving_expo)
{
	if (search_home(saving_expo, "HOME") == 0)
	{
		perror("minishell: cd");
		return (0);
	}
	else if (p[1] == NULL && search_home(saving_expo, "HOME") == 1)
		chdir(getenv("HOME"));
	else if ((!ft_strcmp(p[1], "~")) && search_home(saving_expo, "HOME") == 1)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else if (chdir(p[1]))
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(p[1], 1);
		write(1, ": ", 2);
		write(1, "No such file or directory\n", 26);
		return (0);
	}
	return (1);
}

void	big_cd(t_list **saving_env, t_list **saving_expo, t_args *p)
{
	char	old_pwd[256];
	char	new_pwd[256];

	getcwd (old_pwd, 256);
	if (cd(p->args, (*saving_expo)) == 1)
	{
		getcwd(new_pwd, 256);
		add_oldpwd(saving_env, old_pwd);
		if (search_home(*saving_env, "PWD") == 1)
			modify_pwd(saving_env, new_pwd);
		add_oldpwd(saving_expo, old_pwd);
		if (search_home(*saving_env, "PWD") == 1)
			modify_pwd(saving_expo, new_pwd);
	}
}
