/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:00:26 by aelbouab          #+#    #+#             */
/*   Updated: 2024/09/16 17:22:12 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freearray(char **cav, char *sav)
{
	int	i;

	i = 0;
	if (cav)
	{
		while (cav[i])
		{
			free (cav[i]);
			i++;
		}
		free (cav);
		cav = NULL;
	}
	free(sav);
}

int	*testnsplite(char **av, int *a, int i, int x)
{
	char	**cav;
	char	*sav;
	int		j;
	int		eto;

	a = malloc(sizeof(int) * (x + 1));
	if (!a)
		return (NULL);
	x = -1;
	while (av[++i])
	{
		j = -1;
		sav = rmspace(av[i]);
		cav = ft_split(sav, ' ');
		while (cav[++j])
		{
			eto = ft_atoi(cav[j]);
			if (!eto)
				return (freearray(cav, sav), free (a), NULL);
			a[++x] = eto;
		}
		freearray(cav, sav);
	}
	a[++x] = 0;
	return (a);
}

int	intlen(int *arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

char	**ft_tr(int ac, char **av)
{
	char	**tr;
	int		i;

	i = 0;
	tr = malloc(sizeof(char *) * (ac + 1));
	if (!tr)
		return (NULL);
	while (av[i])
	{
		tr[i] = ft_strtrim(av[i], " \t\v\r\f\n");
		if (!tr[i])
			return (freearray(tr, NULL), NULL);
		i++;
	}
	tr[i] = NULL;
	return (tr);
}

int	*parssing(int ac, char **av)
{
	int		i;
	int		x;
	int		*a;
	char	**tr;

	a = NULL;
	tr = ft_tr(ac, av);
	if (testdigit(ac, tr))
		return (freearray(tr, NULL), NULL);
	x = spacelloc(ac, tr, 1, 0);
	if (!x)
		return (freearray(tr, NULL), NULL);
	a = testnsplite(tr, a, 0, x);
	if (!a)
		return (freearray(tr, NULL), NULL);
	i = intlen(a);
	freearray(tr, NULL);
	if (i != 4 && i != 5)
		return (printf ("need 4 or 5 Arguments\n"), free(a), NULL);
	return (a);
}
