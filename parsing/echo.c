/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:23:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/16 17:41:40 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

int	ft_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
}

static int	ft_check_n(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_m_list *list, int s)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	while (list->dup_com && list->dup_com[i])
	{
		if (ft_check_n(list->dup_com[i]) && x == 0)
			s = 1;
		else
		{
			if (list->dup_com[i])
				ft_putstr(list->dup_com[i]);
			if (i < ft_len(list->dup_com) - 1)
				write (1, " ", 1);
			x = 1;
		}
		if (list->dup_com[i])
			i++;
	}
	if (!s)
		write (1, "\n", 1);
}
