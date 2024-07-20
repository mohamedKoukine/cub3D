/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:59:39 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/20 11:35:49 by mkaoukin         ###   ########.fr       */
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

static int    size_j(long nb)
{
    int    j;

    j = 1;
    while (nb > 9)
    {
        nb = nb / 10;
        j++;
    }
    return (j);
}

char    *ft_itoa(int n)
{
    char    *r;
    int        j;
    long    nb;

    j = 1;
    nb = n;
    if (n < 0)
    {
        nb = -nb;
        j = 2;
    }
    r = (char *)malloc(sizeof(char) * (j = size_j(nb) + j));
    if (!r)
        return (NULL);
    j--;
    r[j] = '\0';
    while (j > 0)
    {
        j--;
        r[j] = (nb % 10) + 48;
        nb = nb / 10;
        if (j == 0 && n < 0)
            r[j] = '-';
    }
    return (r);
}
