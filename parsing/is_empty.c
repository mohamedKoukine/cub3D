/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:23:38 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/05 10:32:55 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

t_m_list	*telda_to_home(t_m_list *list, t_list *lst, char *home)
{
	t_m_list	*tmp;
	char		*home1;
	int			i;

	i = 0;
	tmp = list;
	home = get_home1();
	home1 = get_home(lst);
	while (tmp)
	{
		while (tmp->d_com[i])
		{
			if (!ft_strcmp(tmp->d_com[i], "~"))
			{
				free(tmp->d_com[i]);
				if (home1)
					tmp->d_com[i] = strdup(home1);
				else
					tmp->d_com[i] = strdup(home);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (list);
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
