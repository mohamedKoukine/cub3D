/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:02:18 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/10/27 15:34:25 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	player_angle(t_all *all)
{
	if (all->player->pl_dir == 'N')
		all->player->angle = (3 * M_PI) / 2 ;
	else if (all->player->pl_dir == 'S')
		all->player->angle = M_PI / 2;
	else if (all->player->pl_dir == 'E')
		all->player->angle = 0;
	else if (all->player->pl_dir == 'W')
		all->player->angle = M_PI;
}

int	beetwen(t_all *all, float yend, float xend)
{
	if ((all->cub->lines[((int)yend + 1) / Q_SIZE][(int)xend / Q_SIZE] == '1'
		&& all->cub->lines[(int)yend / Q_SIZE][((int)xend + 1) / Q_SIZE] == '1')
		|| (all->cub->lines[((int)yend + 1) / Q_SIZE][(int)xend / Q_SIZE] == '1'
		&& all->cub->lines[(int)yend / Q_SIZE][((int)xend - 1) / Q_SIZE] == '1')
		|| (all->cub->lines[((int)yend - 1) / Q_SIZE][(int)xend / Q_SIZE] == '1'
		&& all->cub->lines[(int)yend / Q_SIZE][((int)xend - 1) / Q_SIZE] == '1')
		|| (all->cub->lines[((int)yend - 1) / Q_SIZE][(int)xend / Q_SIZE] == '1'
		&& all->cub->lines[(int)yend / Q_SIZE]
			[((int)xend + 1) / Q_SIZE] == '1'))
		return (0);
	return (1);
}

void	hor_point1(t_all *all, float xend, float yend, float ystep)
{
	float	xstep;

	xstep = ystep / tan(all->ray_angle);
	while (((xend) >= 0 && (yend) >= 0)
		&& (xend / Q_SIZE) < (all->cub->width / Q_SIZE)
		&& (yend / Q_SIZE) < (all->cub->height / Q_SIZE)
		&& all->cub->lines[(int)yend / Q_SIZE]
		&& (xend / Q_SIZE) < (int)ft_strlen(all->cub->lines[(int)yend / Q_SIZE],
			0)
		&& all->cub->lines[(int)yend / Q_SIZE][(int)xend / Q_SIZE] != ' '
		&& all->cub->lines[(int)yend / Q_SIZE][(int)xend / Q_SIZE] != '1'
		&& beetwen(all, yend, xend))
	{
		xend += xstep;
		yend += ystep;
	}
	if (xend < 0)
		xend = 0;
	all->hor_p_x = xend;
	all->hor_p_y = yend;
}

void	hor_point(t_all *all, float angle)
{
	float	yend;
	float	xend;
	float	ystep;

	all->player->ox = (all->player->x) + 50;
	all->player->oy = (all->player->y) + 50;
	if (angle > 0 && angle < M_PI)
	{
		yend = floor (all->player->oy / Q_SIZE) * Q_SIZE + Q_SIZE;
		ystep = Q_SIZE;
	}
	if (!(angle > 0 && angle < M_PI))
	{
		yend = floor (all->player->oy / Q_SIZE) * Q_SIZE - 0.001f;
		ystep = -1 * Q_SIZE;
	}
	xend = all->player->ox + ((yend - all->player->oy) / tan(angle));
	hor_point1(all, xend, yend, ystep);
}

int	point_ch(t_all *all, float san, float can)
{
	all->player->a[1] = (all->player->x + can) / Q_SIZE;
	all->player->a[0] = (all->player->y + san) / Q_SIZE;
	all->player->b[1] = ((all->player->x + 200) + can) / Q_SIZE;
	all->player->b[0] = (all->player->y + san) / Q_SIZE;
	all->player->c[1] = ((all->player->x + 200) + can) / Q_SIZE;
	all->player->c[0] = ((all->player->y + 200) + san) / Q_SIZE;
	all->player->d[1] = (all->player->x + can) / Q_SIZE;
	all->player->d[0] = ((all->player->y + 200) + san) / Q_SIZE;
	if (!all->cub->lines[(int)all->player->a[0]]
		|| !all->cub->lines[(int)all->player->b[0]]
		|| !all->cub->lines[(int)all->player->c[0]]
		|| !all->cub->lines[(int)all->player->d[0]])
		return (1);
	if (all->cub->lines[(int)all->player->a[0]]
		[(int)all->player->a[1]] == '1'
		|| all->cub->lines[(int)all->player->b[0]]
		[(int)all->player->b[1]] == '1'
		|| all->cub->lines[(int)all->player->c[0]]
		[(int)all->player->c[1]] == '1'
		|| all->cub->lines[(int)all->player->d[0]]
		[(int)all->player->d[1]] == '1')
		return (1);
	return (0);
}
