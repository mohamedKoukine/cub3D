/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:08:23 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/09 13:50:05 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_fc(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < all->res_h)
	{
		j = 0;
		while (j < all->res_w)
		{
			if (i < all->res_h / 2)
			{
				mlx_put_pixel(all->cub->img, j, i, ft_color(all->cub->c[0],
						all->cub->c[1], all->cub->c[2], 255));
			}
			else
			{
				mlx_put_pixel(all->cub->img, j, i, ft_color(all->cub->ff[0],
						all->cub->ff[1], all->cub->ff[2], 255));
			}
			j++;
		}
		i++;
	}
}

void	draw_texture1(t_all *all, float wall_h, int text_of_x, int i)
{
	int	y;
	int	text_of_y;
	int	wall_bottom_px;
	int	wall_top_px;
	int	index;

	y = 0;
	wall_top_px = (all->res_h / 2) - ((int) wall_h / 2);
	wall_bottom_px = (all->res_h / 2) + ((int) wall_h / 2);
	if (y < wall_top_px)
		y = wall_top_px;
	while (y < wall_bottom_px && y < all->res_h)
	{
		text_of_y = (y - wall_top_px)
			* ((float) all->cub->texture[i]->height) / ((float)(wall_h));
		index = ((all->cub->texture[i]->width * text_of_y) + text_of_x) * 4;
		all->cub->pixel = all->cub->texture[i]->pixels[index];
		all->cub->pixel1 = all->cub->texture[i]->pixels[index + 1];
		all->cub->pixel2 = all->cub->texture[i]->pixels[index + 2];
		all->cub->pixel3 = all->cub->texture[i]->pixels[index + 3];
		mlx_put_pixel(all->cub->img, all->x, y++,
			ft_color(all->cub->pixel, all->cub->pixel1,
				all->cub->pixel2, all->cub->pixel3));
	}
}

void	draw_texture(t_all *all, float wall_h, int i)
{
	int	text_of_x;

	if (dest_vita1(all))
		i = 1;
	if (i && !(all->ray_angle > 0 && all->ray_angle < M_PI))
		i = 2;
	else if (i && (all->ray_angle > 0 && all->ray_angle < M_PI))
		i = 3;
	else if (!i && (all->ray_angle >= M_PI_2 && all->ray_angle < 3 * M_PI_2))
		i = 1;
	if (i == 2 || i == 3)
		text_of_x = (((int) all->hor_p_x % Q_SIZE)
				* all->cub->texture[i]->width / Q_SIZE);
	else
		text_of_x = (((int) all->ver_p_y % Q_SIZE)
				* all->cub->texture[i]->width / Q_SIZE);
	draw_texture1(all, wall_h, text_of_x, i);
	if (all->x < all->res_w)
		all->x++;
	else
		all->x = 0;
}

void	draw_3d(t_all *all)
{
	float	wall_h;
	int		numray;
	float	dpp;
	float	res;

	dpp = (all->res_w / 2) / tan(deg_to_rad(30));
	numray = 0;
	while (numray <= all->res_w)
	{
		hor_point(all, all->ray_angle);
		ver_point(all, all->ray_angle);
		res = dest_vita2(all);
		wall_h = (Q_SIZE / res) * dpp;
		draw_texture(all, wall_h, 0);
		all->ray_angle += deg_to_rad(60) / all->res_w;
		if (all->ray_angle < 0)
			all->ray_angle += 2 * M_PI;
		else if (all->ray_angle >= 2 * M_PI)
			all->ray_angle -= 2 * M_PI;
		numray++;
	}
}
