/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:44:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 15:13:04 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

static void	cheng_pwd(t_list *lst, char *old_pwd, t_list *tmp, char *str)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD") && i == 0)
		{
			old_pwd = ft_strdup(tmp->ex);
			freethis(tmp->env, tmp->ex);
			tmp->ex = str;
			tmp->env = ft_strjoin("PWD=", tmp->ex, 1);
			tmp = lst;
			i = 1;
			continue ;
		}
		if (!ft_strcmp(tmp->key, "OLDPWD") && i == 1)
		{
			freethis(tmp->env, tmp->ex);
			tmp->env = ft_strjoin("OLDPWD=", old_pwd, 1);
			tmp->check_aff = 0;
			tmp->ex = old_pwd;
			break ;
		}
		tmp = tmp->next;
	}
}

static int	check_dir(t_list *lst, t_m_list *list)
{
	char	*pwd;
	char	*tmp;

	pwd = is_pwd(lst);
	chdir(list->dup_com[1]);
	if (getcwd(NULL, 0) == NULL)
	{
		if (!ft_strcmp(list->dup_com[1], ".."))
		{
			printf ("cd: error retrieving current directory: getcwd: cannot "
				"access parent directories: No such file or directory\n");
			tmp = ft_strjoin(pwd, "/..", 1);
			cheng_pwd(lst, pwd, lst, tmp);
			return (1);
		}
	}
	return (0);
}

static void	cd_empty(t_fd *fd, t_list *lst)
{
	char	*home;

	home = get_home(lst);
	if (home && home[0])
	{
		if (chdir(home) == -1)
		{
			printf ("minishell: %s: No such file or directory\n", home);
			fd->ex_c = 1;
		}
	}
	else
	{
		printf ("minishell: cd: HOME not set\n");
		fd->ex_c = 1;
	}
}

static void	cd_return(t_fd *fd, char *old_pwd)
{
	if (chdir(old_pwd) == -1)
	{
		printf ("minishell: cd: OLDPWD not set\n");
		fd->ex_c = 1;
		return ;
	}
	else
		printf("%s\n", old_pwd);
}

void	ft_cd(t_list *lst, t_m_list *list, t_fd *fd)
{
	char	*old_pwd;
	int		i;

	old_pwd = oldisgold(lst);
	if (getcwd(NULL, 0) == NULL)
	{
		i = check_dir (lst, list);
		if (i == 1)
			return ;
	}
	else if (!list->dup_com[1])
		cd_empty(fd, lst);
	else if (!ft_strcmp(list->dup_com[1], "-"))
		cd_return(fd, old_pwd);
	else
	{
		if (chdir(list->dup_com[1]) == -1)
		{
			printf("minishell: %s: No such file or directory\n",
				list->dup_com[1]);
			fd->ex_c = 1;
		}
	}
	cheng_pwd(lst, old_pwd, lst, getcwd(NULL, 0));
}
