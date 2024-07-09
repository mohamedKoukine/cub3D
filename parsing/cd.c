/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:44:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/08 16:28:52 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*get_home(t_list *lst)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, "HOME"))
			return (lst->ex);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_cd(t_list *lst, t_m_list *list)
{
	t_list	*tmp = lst;
	char	buf[PATH_MAX];
	char	*old_pwd;
	int		i;

	i = 0;
	if (!list->dup_com[1])
		chdir(get_home(lst));
	if (chdir(list->dup_com[1]) == -1)
		printf ("minishell: %s: No such file or directory\n", list->dup_com[1]);
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			old_pwd = tmp->ex;
			free(tmp->env);
			tmp->env = ft_strjoin("PWD=", getcwd(buf, PATH_MAX));
			tmp->ex = getcwd(buf, PATH_MAX);
		}
		else if (!ft_strcmp(tmp->key, "OLD_PWD"))
		{
			free(tmp->env);
			tmp->env = ft_strjoin("OLD_PWD=", old_pwd);
			tmp->ex = old_pwd;
			i = 1;
		}
		tmp = tmp->next;
	}
	if (i == 0)
	{
		tmp = ft_lstnew1(ft_strjoin("OLD_PWD=", old_pwd), 0, 0);
		ft_lstadd_back_env(&lst, tmp);
	}
}
