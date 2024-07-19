/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:20:13 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/16 16:41:54 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

void	ft_lstadd_back(t_m_list **lst, t_m_list *new)
{
	t_m_list	*y;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	y = ft_lstlast(*lst);
	y->next = new;
}

void	ft_lstadd_back_env(t_list **lst, t_list *new)
{
	t_list	*d;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	d = ft_lstlast_env(*lst);
	d->next = new;
}


t_m_list	*ft_lstlast(t_m_list *lst)
{
	t_m_list	*p;

	if (!lst)
		return (NULL);
	p = lst;
	while (p->next)
	{
		p = p->next;
	}
	return (p);
}

t_list	*ft_lstlast_env(t_list *lst)
{
	t_list	*p;

	if (!lst)
		return (NULL);
	p = lst;
	while (p->next)
	{
		p = p->next;
	}
	return (p);
}

t_m_list	*ft_lstnew(char *content, char **com)
{
	t_m_list	*node;

	if (!com)
		return (NULL);
	node = malloc(sizeof(t_m_list));
	if (!node)
		return (NULL);
	node->command = content;
	node->d_com = com;
	node->first_comm = *com;
	node->d_h = NULL;
	node->file = NULL;
	node->next = NULL;
	node->dup_com = NULL;
	node->ptr_unset = NULL;
	return (node);
}
