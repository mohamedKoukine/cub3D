/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:36:47 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/15 11:34:26 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_cub3D.h"

int	ft_atoi(const char *str)
{
	long	rev;
	long	i;
	int		tmp;
	long	j;

	i = 0;
	rev = 0;
	j = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rev = rev * 10 + (str[i] - 48);
		tmp = rev;
		if (tmp != rev)
			return (-1);
		i++;
	}
	return (rev * j);
}
