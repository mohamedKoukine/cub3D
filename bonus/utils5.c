/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:08:23 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/15 16:24:24 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_cub3D.h"

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

// void	draw_mini(t_all *all)
// {
// 	float	xend;
// 	float	yend;
// 	int		numray;

// 	numray = 0;
// 	while (numray <= all->res_w)
// 	{
// 		hor_point(all, all->ray_angle);
// 		ver_point(all, all->ray_angle);
// 		if (dest_vita1(all) == 1)
// 		{
// 			xend = all->hor_p_x;
// 			yend = all->hor_p_y;
// 			draw_line(all, xend, yend, ft_color(255, 0, 0, 255));
// 		}
// 		else
// 		{
// 			xend = all->ver_p_x;
// 			yend = all->ver_p_y;
// 			draw_line(all, xend, yend, ft_color(0, 255, 0, 255));
// 		}
// 		all->ray_angle += deg_to_rad(60) / all->res_w;
// 		if (all->ray_angle < 0)
// 			all->ray_angle += 2 * M_PI;
// 		else if (all->ray_angle >= 2 * M_PI)
// 			all->ray_angle -= 2 * M_PI;
// 		numray++;
// 	}
// 	draw_player(all, ft_color(251,65,88, 255));
// }

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
	{
		if (!all->flag_door)
			text_of_x = (((int) all->hor_p_x % Q_SIZE)
					* all->cub->texture[i]->width / Q_SIZE);
		else
			text_of_x = (((int) all->hor_p_x % Q_SIZE)
					* all->cub->texture[4]->width / Q_SIZE);
	}
	else
	{
		if (!all->flag_door)
			text_of_x = (((int) all->ver_p_y % Q_SIZE)
					* all->cub->texture[i]->width / Q_SIZE);
		else
			text_of_x = (((int) all->ver_p_y % Q_SIZE)
					* all->cub->texture[4]->width / Q_SIZE);
	}
	if (!all->flag_door)
		draw_texture1(all, wall_h, text_of_x, i);
	else
		draw_texture1(all, wall_h, text_of_x, 4);
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
		if (dest_vita1(all) && ((int)all->hor_p_x / Q_SIZE) < (int)ft_strlen(all->cub->lines[(int)all->hor_p_y / Q_SIZE],
            0) && all->cub->lines[(int)all->hor_p_y / Q_SIZE][(int)all->hor_p_x / Q_SIZE] == 'D')
            all->flag_door = 1;
        else if (!dest_vita1(all) && ((int)all->ver_p_x / Q_SIZE) < (int)ft_strlen(all->cub->lines[(int)all->ver_p_y/ Q_SIZE],
            0) && all->cub->lines[(int)all->ver_p_y / Q_SIZE][(int)all->ver_p_x / Q_SIZE] == 'D')
            all->flag_door = 1;
        else
            all->flag_door = 0;
		draw_texture(all, wall_h, 0);
		all->ray_angle += deg_to_rad(60) / all->res_w;
		if (all->ray_angle < 0)
			all->ray_angle += 2 * M_PI;
		else if (all->ray_angle >= 2 * M_PI)
			all->ray_angle -= 2 * M_PI;
		numray++;
	}
}
