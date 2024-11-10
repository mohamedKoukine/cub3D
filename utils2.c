/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:58:15 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/09 16:10:26 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_all *all, int color)
{
	int	i;
	int	j;
	int	y;
	int	x;

	i = 0;
	y = all->player->y;
	x = all->player->x - 1;
	while (i <= 7)
	{
		j = 0;
		x = all->player->x - 1;
		while (j <= 7)
		{
			mlx_put_pixel(all->cub->img, x, y, color);
			j++;
			x++;
		}
		y++;
		i++;
	}
}

void	draw_mp(t_all *all, char c)
{
	if (c == '1')
		draw_map(all, ft_color(17, 0, 199, 255), 1);
	else if (c == '0')
		draw_map(all, ft_color(255, 255, 255, 255), 0);
}

void	ft_draw_map(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	all->x = 0;
	while (all->cub->lines[i])
	{
		j = 0;
		while (all->cub->lines[i][j])
		{
			all->cub->x = j * Q_SIZE;
			all->cub->y = i * Q_SIZE;
			if (all->cub->lines[i][j] == 'E' || all->cub->lines[i][j] == 'N'
				|| all->cub->lines[i][j] == 'W' || all->cub->lines[i][j] == 'S')
			{
				all->player->x = j * Q_SIZE;
				all->player->y = i * Q_SIZE;
				all->player->pl_dir = all->cub->lines[i][j];
				all->cub->lines[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}
