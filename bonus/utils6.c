/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:21:50 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/15 11:35:27 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_cub3D.h"

void	ft_error(char *s, t_cub *cub, int index)
{
	if (index)
		printf ("Error\n cub3D: %s\n", s);
	if (cub && cub->d)
		freeall(cub->d);
	if (cub && cub->l)
		free (cub->l);
	if (cub && cub->lines)
		freeall(cub->lines);
	exit (1);
}

void	check_number(t_cub *cub, int j, int i, int l)
{
	char	*d;

	while (cub->d[j][i] == 32)
		i++;
	l = i--;
	while (cub->d[j][++i])
	{
		if (cub->d[j][i] == ',')
		{
			d = ft_substr(cub->d[j], l, i - l);
			l = ft_atoi(d);
			free (d);
			if (!(l >= 0 && l <= 225))
				ft_error ("number C or F not valide", cub, 1);
			l = i + 1;
		}
		else if (cub->d[j][i + 1] == '\0')
		{
			d = ft_substr(cub->d[j], l, i - l + 1);
			l = ft_atoi(d);
			free (d);
			if (!(l >= 0 && l <= 225))
				ft_error ("number C or F not valide", cub, 1);
		}
	}
}

int	check_f_c(t_cub *cub, int i, int j, int k)
{
	int	d;

	d = i - 2;
	while (cub->d[j][i] == 32)
		i++;
	if (cub->d[j][i] >= '0' && cub->d[j][i] <= '9')
	{
		while ((cub->d[j][i] >= '0' && cub->d[j][i] <= '9')
				|| cub->d[j][i] == ',')
		{
			if (cub->d[j][i] == ',')
			{
				if (cub->d[j][i + 1] == ',')
					ft_error("map is not valide", cub, 1);
				k++;
			}
			i++;
		}
		if (cub->d[j][i - 1] == ',' || cub->d[j][i] || k != 2)
			ft_error("map is not valide", cub, 1);
		check_number(cub, j, 1, 0);
	}
	else
		ft_error("map not valide", cub, 1);
	return (d);
}

void	check_png(char *s, int i, t_cub *cub)
{
	int	j;

	j = 2;
	if (s[0] == 'S')
		i = 1;
	else if (s[0] == 'W')
		i = 2;
	while (s[j] == 32)
		j++;
	if (ft_strlen(&s[j], 0) < 5)
		ft_error("image is not png", cub, 1);
	if (ft_strcmp(".png", &s[ft_strlen(s, 0) - 4]))
		ft_error("image is not png", cub, 1);
	cub->f[i]++;
}

void	check_valid_con(t_cub *cub, int j, int i)
{
	if ((cub->d[j][i] == 'N' && cub->d[j][i + 1] == 'O')
		|| (cub->d[j][i] == 'S' && cub->d[j][i + 1] == 'O')
		|| (cub->d[j][i] == 'W' && cub->d[j][i + 1] == 'E'))
		check_png(cub->d[j], 0, cub);
	else if (cub->d[j][i] == 'E' && cub->d[j][i + 1] == 'A')
		check_png(cub->d[j], 3, cub);
	else if (cub->d[j][i] == 'F' && cub->d[j][i + 1] == ' ')
	{
		i = check_f_c(cub, i + 1, j, 0);
		cub->f[4]++;
	}
	else if (cub->d[j][i] == 'C' && cub->d[j][i + 1] == ' ')
	{
		i = check_f_c(cub, i + 1, j, 0);
		cub->f[5]++;
	}
	else
		ft_error("map not valide1", cub, 1);
	i += 2;
	if (cub->d[j][i] == 32)
		i++;
	else
		ft_error("map not valide2", cub, 1);
	if (!cub->d[j][i])
		ft_error("map not valide3", cub, 1);
}
