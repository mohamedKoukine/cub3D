/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:06:44 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/05/24 11:26:14 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*d;

	if (!lst)
		return (NULL);
	d = lst;
	while (d->next)
	{
		d = d->next;
	}
	return (d);
}
