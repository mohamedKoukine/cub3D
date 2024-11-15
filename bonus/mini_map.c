/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:57:10 by aelbouab          #+#    #+#             */
/*   Updated: 2024/11/15 12:00:03 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_cub3D.h"

void	draw_line(t_all *all)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	x = 102;
	y = 102;
	while (i <= 10)
	{
		mlx_put_pixel(all->cub->img, x, y, ft_color(251, 65, 88, 255));
		x += cos(all->player->angle);
		y += sin(all->player->angle);
		i++;
	}
}

void	draw_out(t_all *all, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i <= 210)
	{
		j = 0;
		while (j <= 210)
		{
			if ((i < 9) + (j < 9) + (i > 201) + (j > 201))
				mlx_put_pixel(all->cub->img, j, i, color);
			j++;
		}
		i++;
	}
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
	while (++i < 10)
	{
		j = 0;
		x = all->cub->x;
		while (j < 10)
		{
			if (type == 1 && (all->cub->y == y || all->cub->x == x
					|| j == 10 || i == 10))
				mlx_put_pixel(all->cub->img, x,
					y, ft_color (0, 0, 0, 255));
			else
				mlx_put_pixel(all->cub->img, x, y, color);
			j++;
			x++;
		}
		y++;
	}
}

void	draw_mp(t_all *all, char c)
{
	if (c == '1' && all->cub->x >= 0 && all->cub->x <= 200
		&& all->cub->y >= 0 && all->cub->y <= 200)
		draw_map(all, ft_color(255, 255, 255, 255), 1);
	else if (c == 'D' && all->cub->x >= 0 && all->cub->x <= 200
		&& all->cub->y >= 0 && all->cub->y <= 200)
		draw_map(all, ft_color(112, 182, 204, 255), 1);
	else if (c == 'd' && all->cub->x >= 0 && all->cub->x <= 200
		&& all->cub->y >= 0 && all->cub->y <= 200)
		draw_map(all, ft_color(111, 239, 77, 255), 1);
}

void	draw_minimap(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	draw_line(all);
	while (all->cub->lines[i])
	{
		j = 0;
		while ((size_t)j < ft_strlen(all->cub->lines[i], 0))
		{
			all->cub->x = (j * 10) + ((200 / 2) - all->player->x_mini);
			all->cub->y = (i * 10) + ((200 / 2) - all->player->y_mini);
			draw_mp(all, all->cub->lines[i][j]);
			j++;
		}
		i++;
	}
	draw_out(all, ft_color(0, 0, 0, 255));
	draw_player(all, ft_color(251, 65, 88, 255));
}
