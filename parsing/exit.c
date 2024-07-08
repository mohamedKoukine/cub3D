/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:05 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/04 16:08:45 by aelbouab         ###   ########.fr       */
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

void	my_exit(t_m_list *list)
{
	if (!list->dup_com[1] || !list->dup_com[1][0])
		exit(0);
	if (all_digit(list->dup_com[1]))
		exit(ft_atoi(list->dup_com[1]) % 256);
	else
		exit(255);
}