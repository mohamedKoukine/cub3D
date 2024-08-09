/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:23:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/05 11:14:43 by mkaoukin         ###   ########.fr       */
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

static int	ft_check_n(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-')
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

	i = 1;
	while (list->dup_com && list->dup_com[i])
	{
		if (ft_check_n(list->dup_com[i]))
			s = 1;
		else
		{
			if (list->dup_com[i])
				printf("%s", list->dup_com[i]);
			if (i < ft_len(list->dup_com) - 1)
				printf(" ");
		}
		if (list->dup_com[i])
			i++;
	}
	if (!s)
		printf("\n");
}
