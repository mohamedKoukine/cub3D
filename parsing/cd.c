/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:44:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/02 12:02:56 by mkaoukin         ###   ########.fr       */
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

void	cheng_pwd(t_list *lst, char *old_pwd, t_list *tmp)
{
	int	i;

	i = 0;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD") && i == 0)
		{
			old_pwd = ft_strdup(tmp->ex);
			free(tmp->env);
			if (tmp->ex)
				free(tmp->ex);
			tmp->ex = getcwd(NULL, 0);
			tmp->env = ft_strjoin("PWD=", tmp->ex, 1); // LEAKS DETECTED
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
}

void	ft_cd(t_list *lst, t_m_list *list, t_fd *fd)
{
	char	*old_pwd;
	char	*home;

	old_pwd = oldisgold(lst);
	home = get_home(lst);
	if (!list->dup_com[1])
	{
		if (home && home[0])
		{
			if(chdir(home) == -1)
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
	cheng_pwd(lst, old_pwd, lst);
}
