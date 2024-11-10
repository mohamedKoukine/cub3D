/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:52:18 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/10/27 10:35:01 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_map(t_all *all, int color, int type)
{
	int	i;
	int	j;
	int	y;
	int	x;

	i = -1;
	y = all->cub->y;
	x = all->cub->x;
	while (++i < Q_SIZE)
	{
		j = 0;
		all->cub->x = x;
		while (j < Q_SIZE)
		{
			if (type == 1 && (all->cub->y == y || all->cub->x == x
					|| j == Q_SIZE || i == Q_SIZE))
				mlx_put_pixel(all->cub->img, all->cub->x,
					all->cub->y, ft_color (0, 0, 0, 255));
			else
				mlx_put_pixel(all->cub->img, all->cub->x, all->cub->y, color);
			j++;
			all->cub->x++;
		}
		all->cub->y++;
	}
}

size_t	long_line(t_cub *cub)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (cub->lines[i])
	{
		if (j < ft_strlen(cub->lines[i], 1))
			j = ft_strlen(cub->lines[i], 1);
		i++;
	}
	return (j);
}

int	h_map(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->lines[i])
		i++;
	return (i);
}

double	deg_to_rad(double an)
{
	return (an * (M_PI / 180));
}
