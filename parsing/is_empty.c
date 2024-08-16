/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:23:38 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/13 12:32:44 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/ex_minishell.h"

void	chang_oldpwd(t_list *tmp, char *old_pwd, int *j)
{
	freethis(tmp->env, tmp->ex);
	tmp->env = ft_strjoin("OLDPWD=", old_pwd, 1);
	tmp->check_aff = 0;
	tmp->ex = old_pwd;
	*j = 1;
}

void	telda_to_home0(t_m_list *list, t_list *lst, char *home, t_m_list *tmp)
{
	int		i;
	char	*home1;
	char	*tofree;

	i = -1;
	home1 = get_home(lst);
	while (tmp->d_com[++i])
	{
		if (!ft_strcmp(tmp->d_com[i], "~")
			|| !ft_strncmp(tmp->d_com[i], "~/", 2))
		{
			tofree = tmp->d_com[i];
			if (home1)
				tmp->d_com[i] = ft_strjoin(home1, &tmp->d_com[i][1], 1);
			else
				tmp->d_com[i] = ft_strjoin(home, &tmp->d_com[i][1], 1);
			if (!tmp->d_com[i])
				ft_mallocerr(list, lst, home, NULL);
			free(tofree);
		}
	}
}

t_m_list	*telda_to_home(t_m_list *list, t_list *lst, char *home)
{
	t_m_list	*tmp;

	tmp = list;
	home = get_home1(lst, list);
	while (tmp)
	{
		telda_to_home0(list, lst, home, tmp);
		tmp = tmp->next;
	}
	return (free (home), list);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		else
			return (0);
	}
	free (line);
	return (1);
}
