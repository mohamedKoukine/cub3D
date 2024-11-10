/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:04:27 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/10/27 10:46:12 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ver_point1(t_all *all, float xend, float yend, float xstep)
{
	float	ystep;

	ystep = xstep * tan(all->ray_angle);
	while (((xend / Q_SIZE) >= 0 && (yend / Q_SIZE) >= 0)
		&& (xend / Q_SIZE) < (all->cub->width / Q_SIZE)
		&& (yend / Q_SIZE) < (all->cub->height / Q_SIZE)
		&& all->cub->lines[(int)yend / Q_SIZE]
		&& (xend / Q_SIZE) < (int)ft_strlen(all->cub->lines[
				(int)yend / Q_SIZE], 0)
		&& all->cub->lines[(int)yend / Q_SIZE][(int)xend / Q_SIZE] != ' '
		&& all->cub->lines[(int)yend / Q_SIZE][(int)xend / Q_SIZE] != '1'
		&& beetwen(all, yend, xend))
	{
		xend += xstep;
		yend += ystep;
	}
	all->ver_p_x = xend;
	if (yend < 0)
		yend = 0;
	all->ver_p_y = yend;
}

void	ver_point(t_all *all, float angle)
{
	float	yend;
	float	xend;
	float	xstep;

	all->player->ox = all->player->x + 50;
	all->player->oy = all->player->y + 50;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI))
	{
		xend = floor (all->player->ox / Q_SIZE) * Q_SIZE - 0.001f;
		xstep = -1 * Q_SIZE;
	}
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
	{
		xend = floor (all->player->ox / Q_SIZE) * Q_SIZE + Q_SIZE ;
		xstep = Q_SIZE;
	}
	yend = all->player->oy + ((xend - all->player->ox) * tan(angle));
	ver_point1 (all, xend, yend, xstep);
}

float	dest_vita1(t_all *all)
{
	float	d_hor;
	float	d_ver;

	d_hor = sqrt(pow(all->hor_p_x - all->player->ox, 2)
			+ pow(all->hor_p_y - all->player->oy, 2));
	d_ver = sqrt(pow(all->ver_p_x - all->player->ox, 2)
			+ pow(all->ver_p_y - all->player->oy, 2));
	if (d_hor < d_ver)
		return (1);
	return (0);
}

float	dest_vita2(t_all *all)
{
	float	d_hor;
	float	d_ver;

	d_hor = sqrt(pow(all->hor_p_x - all->player->ox, 2)
			+ pow(all->hor_p_y - all->player->oy, 2));
	d_ver = sqrt(pow(all->ver_p_x - all->player->ox, 2)
			+ pow(all->ver_p_y - all->player->oy, 2));
	if (d_hor < d_ver)
		return (d_hor * cos(all->player->angle - all->ray_angle));
	return (d_ver * cos(all->player->angle - all->ray_angle));
}

void	draw_rm(t_all *all, float wall_h)
{
	int	y;
	int	i;

	i = 0;
	y = all->jump;
	while (i < wall_h / 2)
	{
		mlx_put_pixel(all->cub->img, all->x, y, ft_color(0, 0, 255, 255));
		y--;
		i++;
	}
	y = all->jump;
	while (i < wall_h)
	{
		mlx_put_pixel(all->cub->img, all->x, y, ft_color(0, 0, 255, 255));
		y++;
		i++;
	}
	if (all->x < all->res_w)
		all->x++;
	else
		all->x = 0;
}
