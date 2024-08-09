/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:44:42 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/06 13:20:24 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

int	ft_lstsize(t_m_list *lst)
{
	int			i;
	t_m_list	*d;

	d = lst;
	i = 0;
	while (d)
	{
		d = d -> next;
		i++;
	}
	return (i);
}

int	ft_strchr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_lstsize1(t_list *lst)
{
	int		i;
	t_list	*d;

	d = lst;
	i = 0;
	while (d)
	{
		if (ft_strchr(d->env))
			i++;
		d = d -> next;
	}
	return (i);
}
