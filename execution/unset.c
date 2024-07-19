/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:33:01 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/07/17 12:11:35 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

t_list	*delnode(t_list *lst, t_list *last)
{
	t_list *tmp;

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

t_list *ft_unset1(t_list *lst, t_m_list *list, char *line)
{
	t_list *last;
	t_list *tmp;
	t_list *head;

	last = NULL;
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

t_list *ft_unset(t_list *lst, t_m_list *list, char **line)
{
	int		i;
	int		j;
	t_list *last;

	last = NULL;
	i = 1;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (!ft_isalnum(line[i][j]))
			{
				printf ("minishell: unset: `%s': not a valid identifier\n", line[i]);
				break ;
			}
			j++;
		}
		if (line[i][j] == '\0')
			lst = ft_unset1(lst, list, line[i]);
		i++;
	}
	return (lst);
}
