/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:59:39 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/03 15:08:58 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

int ft_atoi(const char *str)
{
	long	i;
	long	res;
	long	j;
	long	sv;

	i = 0;
	res = 0;
	j = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			j *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sv = res;
		res = res * 10 + (str[i] - 48);
		i++;
		if ((sv != (res / 10)) && (j == 1))
			return (-1);
		if ((sv != (res / 10)) && (j == -1))
			return (0);
	}
	return (res * j);
}