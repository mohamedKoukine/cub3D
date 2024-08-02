/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:05 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/01 18:09:20 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}

int	all_digit(char *str)
{
	int i;

	i = 0;
	if (!str)
		return(0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	my_exit(t_m_list *list, t_fd *fd)
{
	if (!list->dup_com[1] || !list->dup_com[1][0])
	{
		printf ("exit\n"); 
		exit(fd->ex_c);
	}
	if (all_digit(list->dup_com[1]) && !list->dup_com[2] && ft_atoi(list->dup_com[1]) > 0)
	{
		printf ("exit\n");
		exit(ft_atoi(list->dup_com[1]) % 256);
	}
	else if (all_digit(list->dup_com[1]) && list->dup_com[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return ;
	}
	else if (!all_digit(list->dup_com[1]) || list->dup_com[2] || ft_atoi(list->dup_com[1]) < 0)
	{
		printf ("exit\nminishell: exit: %s: numeric argument required\n", list->dup_com[1]);
		exit(255);
	}
}
