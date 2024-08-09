/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:18:25 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/03 17:20:46 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	print_export(t_list *lst, t_list *lst2, int i)
{
	while (lst->next)
	{
		if (ft_strcmp(lst2->env, lst->next->env) > 0
			&& lst2->i == 0 && lst->next->i == 0)
			lst2 = lst->next;
		lst = lst->next;
	}
	if (lst2->i == 0 && lst2->check_aff != 2 && lst2->check_aff != 3)
	{
		i = -1;
		write(1, "declare -x ", 11);
		while (lst2->env[++i])
		{
			write(1, &lst2->env[i], 1);
			if (lst2->env[i] == '=' && lst2->i == 0)
			{
				write(1, "\"", 1);
				lst2->i = 1;
			}
		}
		if (lst2->i == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	lst2->i = 1;
}

void	aff_export(t_list *lst)
{
	t_list	*lst2;
	t_list	*lst3;

	lst2 = lst;
	lst3 = lst;
	while (lst2)
	{
		if (lst2->i == 0)
			print_export(lst, lst2, 0);
		else
			lst2 = lst2->next;
	}
	while (lst3)
	{
		lst3->i = 0;
		lst3 = lst3->next;
	}
}

size_t	ft_strlen_exp(const char *str, char c, int flag)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (flag == 0)
	{
		while (str[i])
			i++;
	}
	else
	{
		while (str[i] && str[i] != c)
			i++;
	}
	return (i);
}

int	ft_posistion(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}
