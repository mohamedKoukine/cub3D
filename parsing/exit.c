/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:05 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/06 16:49:29 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}

int	all_digit(char *str, int l)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (l)
				free (str);
			return (0);
		}
		i++;
	}
	if (l)
		free (str);
	return (1);
}

void	my_exit_con(t_m_list *list, int exit_code)
{
	int	i;

	if (!list->dup_com[1])
	{
		printf ("exit\n");
		free_list(list);
		exit(exit_code);
	}
	if (all_digit(ft_strtrim(list->dup_com[1], " ", 0), 1)
		&& !list->dup_com[2] && list->dup_com[1] && list->dup_com[1][0])
	{
		i = ft_atoi2(list->dup_com[1], list) % 256;
		printf ("exit\n");
		free_list(list);
		exit(i);
	}
}

void	my_exit(t_m_list *list, t_fd *fd, int exit_code)
{
	my_exit_con(list, exit_code);
	if (all_digit(ft_strtrim(list->dup_com[1], " ", 0), 1)
		&& list->dup_com[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		fd->ex_c = 1;
		return ;
	}
	else if (!all_digit(list->dup_com[1], 0) || list->dup_com[1][0] == '\0')
	{
		printf ("exit\nminishell: exit: %s: numeric argument required\n",
			list->dup_com[1]);
		free_list(list);
		exit(255);
	}
}
