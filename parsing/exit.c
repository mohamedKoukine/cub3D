/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:05 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/19 10:06:49 by mkaoukin         ###   ########.fr       */
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

void	my_exit_con(t_m_list *list, int exit_code, t_list *lst, t_fd *fd)
{
	int	i;

	if (!list->dup_com[1])
	{
		if (fd->i == 0)
			write (2, "exit\n", 5);
		free_env(lst);
		free_list(list);
		exit(exit_code);
	}
	if (all_digit(ft_strtrim(list->dup_com[1], " ", 0), 1)
		&& !list->dup_com[2] && list->dup_com[1] && list->dup_com[1][0])
	{
		i = ft_atoi2(list->dup_com[1], list) % 256;
		if (fd->i == 0)
			write (2, "exit\n", 5);
		free_env(lst);
		free_list(list);
		exit(i);
	}
}

void	my_exit(t_m_list *list, t_fd *fd, int exit_code, t_list *lst)
{
	my_exit_con(list, exit_code, lst, fd);
	if (all_digit(ft_strtrim(list->dup_com[1], " ", 0), 1)
		&& list->dup_com[2])
	{
		if (fd->i == 0)
			write (2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 37);
		fd->ex_c = 1;
		return ;
	}
	else if (!all_digit(list->dup_com[1], 0) || list->dup_com[1][0] == '\0')
	{
		if (fd->i == 0)
			write (2, "exit\n", 5);
		write (2, "minishell: exit: ", 17);
		write (2, list->dup_com[1], ft_strlen(list->dup_com[1]));
		write (2, ": numeric argument required\n", 28);
		free_list(list);
		free_env(lst);
		exit(255);
	}
}
