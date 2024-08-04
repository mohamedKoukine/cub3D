/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:33:01 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/03 13:45:47 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

t_list	*delnode(t_list *lst, t_list *last)
{
	t_list	*tmp;

	tmp = lst->next;
	free (lst->env);
	free (lst->key);
	free (lst->ex);
	free (lst);
	lst = NULL;
	if (!last)
		return (tmp);
	last->next = tmp;
	return (last);
}

t_list	*ft_unset1(t_list *lst, t_m_list *list, char *line)
{
	t_list	*last;
	t_list	*tmp;
	t_list	*head;

	last = NULL;
	list->ptr_unset = NULL;
	head = lst;
	while (lst)
	{
		if (!ft_strcmp(lst->key, line))
		{
			tmp = delnode(lst, last);
			if (!last)
			{
				head = tmp;
				lst = tmp;
				list->ptr_unset = lst;
			}
			break ;
		}
		last = lst;
		lst = lst->next;
	}
	return (head);
}

t_list	*ft_unset(t_list *lst, t_m_list *list, char **line, t_fd *fd)
{
	int		i;
	int		j;

	i = 0;
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
		{
			if (!ft_isalnum(line[i][j])
				|| (line[i][0] >= '0' && line[i][0] <= '9'))
			{
				printf ("minishell: unset: `%s': not a valid identifier\n",
					line[i]);
				fd->ex_c = 1;
				break ;
			}
			if (line[i][0] == '_' && line[i][1] == '\0')
				break ;
		}
		if (line[i][j] == '\0')
			lst = ft_unset1(lst, list, line[i]);
	}
	return (lst);
}
