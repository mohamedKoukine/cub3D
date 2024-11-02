/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:56:04 by aelbouab          #+#    #+#             */
/*   Updated: 2024/09/16 13:05:59 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int i)
{
	if ((i >= '0' && i <= '9'))
		return (1);
	return (0);
}

int	testdigit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9' && av[i][j + 1] == '+')
				return (write (2, "Error\n", 6), 1);
			if (av[i][j] == '+' && !(av[i][j + 1] > '0'
				&& av[i][j + 1] <= '9'))
				return (write (2, "Error\n", 6), 1);
			if ((av[i][j] < '0' || av[i][j] > '9') && av[i][j] != '+')
				return (write (2, "Error\n", 6), 1);
			if (av[i][j] == '0' && !ft_isdigit(av[i][j + 1])
				&& !ft_isdigit(av[i][j - 1]))
				return (write (2, "Error\n", 6), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	spacelloc(int ac, char **av, int i, int x)
{
	int	j;
	int	n;

	while (i < ac)
	{
		j = 0;
		n = 0;
		while (av[i][j])
		{
			if ((av[i][j] >= '0' && av[i][j] <= '9')
				|| av[i][j] == '+')
				x++;
			else
				n++;
			while ((av[i][j] >= '0' && av[i][j] <= '9')
					|| av[i][j] == '+')
				j++;
			if (av[i][j])
				j++;
		}
		if (n == (int)ft_strlen(av[i]))
			return (write (2, "Error\n", 6), 0);
		i++;
	}
	return (x);
}

char	*rmspace1(char *av, char *sav, int i, int j)
{
	int		l;
	int		cp;

	l = 0;
	cp = 0;
	while (av[i])
	{
		if (!((av[i] >= 9 && av[i] <= 13) || av[i] == 32))
			j++;
		while (!((av[i] >= 9 && av[i] <= 13) || av[i] == 32) && av[i])
		{
			l++;
			i++;
		}
		if (av[i])
			i++;
	}
	cp = l + j;
	sav = malloc(cp + 1);
	if (!sav)
		return (NULL);
	return (sav);
}

char	*rmspace(char *av)
{
	char	*sav;
	int		i;
	int		j;

	sav = NULL;
	sav = rmspace1(av, sav, 0, 0);
	i = 0;
	j = 0;
	while (av[i])
	{
		while (!((av[i] >= 9 && av[i] <= 13) || av[i] == 32) && av[i])
		{
			sav[j] = av[i];
			j++;
			i++;
			if (((av[i] >= 9 && av[i] <= 13) || av[i] == 32) || av[i] == '\0')
				sav[j++] = ' ';
		}
		if (av[i])
			i++;
	}
	sav[j] = '\0';
	return (sav);
}
