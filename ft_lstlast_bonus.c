/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:29:56 by aelbouab          #+#    #+#             */
/*   Updated: 2024/06/06 16:09:00 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
