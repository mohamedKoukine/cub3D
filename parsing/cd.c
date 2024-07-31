/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:44:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/31 16:01:23 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*get_home(t_list *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, "HOME"))
			return (lst->ex);
		lst = lst->next;
	}
	return (NULL);
}

char	*oldisgold(t_list *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, "OLDPWD"))
			return (lst->ex);
		lst = lst->next;
	}
	return (NULL);
}

int cheng_pwd(t_list *lst, char *old_pwd, t_list *tmp)
{
	char	buf[PATH_MAX];
	int		i;

	i = 0;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD") && i == 0)
		{
			old_pwd = ft_strdup(tmp->ex);
			free(tmp->env);
			if (tmp->ex)
				free(tmp->ex);
			tmp->env = ft_strjoin("PWD=", getcwd(buf, PATH_MAX), 1);
			tmp->ex = ft_strdup(getcwd(buf, PATH_MAX));
			tmp = lst;
			i = 1;
			continue ;
		}
		if (!ft_strcmp(tmp->key, "OLDPWD") && i == 1)
		{
			free(tmp->env);
			if (tmp->ex)
				free(tmp->ex);
			tmp->env = ft_strjoin("OLDPWD=", old_pwd, 1);
			tmp->ex = old_pwd;
			i = 2;
			break ;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	ft_cd(t_list *lst, t_m_list *list, t_fd *fd)
{
	char	*old_pwd;
	int		i;

	old_pwd = oldisgold(lst);
	fd->ex_c = 0;
	if (!list->dup_com[1])
		chdir(get_home(lst));
	else if (!ft_strcmp(list->dup_com[1], "-")) 
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
	else if (chdir(list->dup_com[1]) == -1)
	{
		printf ("minishell: %s: No such file or directory\n", list->dup_com[1]);
		fd->ex_c = 1;
	}
	i = cheng_pwd(lst, old_pwd, lst);
	if (i == 0 || i == 1)
		ft_export(ft_split(ft_strjoin("export OLDPWD=",old_pwd, 1), ' '), lst);
}
