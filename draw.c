/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:54:42 by aelbouab          #+#    #+#             */
/*   Updated: 2024/10/12 16:16:17 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8  | a);
}

void	draw_map(t_all *all, int color, int type)
{
	int i;
	int j;
	int y;
	int x;
	
	i = 0;
	y = all->cub->y;
	x = all->cub->x;
	while(i < q_size)
	{
		j = 0;
		all->cub->x = x;
		while (j < q_size)
		{
			if (type == 1 && (all->cub->y == y || all->cub->x == x || j == q_size || i == q_size))
				mlx_put_pixel(all->cub->img, all->cub->x, all->cub->y, ft_color (0, 0, 0, 255));
			else
				mlx_put_pixel(all->cub->img, all->cub->x, all->cub->y, color);
			j++;
			all->cub->x++;
		}
		all->cub->y++;
		i++;
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

int h_map(t_cub *cub)
{
	int i;

	i= 0;
	while (cub->lines[i])
		i++;
	return (i);
}


double deg_to_rad(double an)
{
	return (an * (M_PI / 180));
}

void	drow_player(t_all *all, int color)
{
	int i;
	int j;
	int y;
	int x;
	
	i = 0;
	y = all->player->y;
	x = all->player->x - 1;
	while(i <=  2)
	{
		j = 0;
		x = all->player->x - 1;
		while (j <= 2)
		{
				mlx_put_pixel(all->cub->img, x, y, color);
			j++;
			x++;
		}
		y++;
		i++;
	}
}

void	ft_draw_map(t_all *all)
{
	int		i;
	int		j;

    i = 0;
	j = 0; 
	while (all->cub->lines[i])
	{
		j = 0;
		while (all->cub->lines[i][j])
		{
			all->cub->x =  j * q_size;
			all->cub->y =  i * q_size;
			if (all->cub->lines[i][j] == 'E' || all->cub->lines[i][j] == 'N'
				|| all->cub->lines[i][j] == 'W' || all->cub->lines[i][j] == 'S')
			{
				all->player->x = j * q_size;
				all->player->y = i * q_size;
				all->player->pl_dir = all->cub->lines[i][j];
				all->cub->lines[i][j] = '0';
			}
			if (all->cub->lines[i][j] == '1')
				draw_map(all, ft_color(17,0,199, 255), 1);
			else if (all->cub->lines[i][j] == '0')
				draw_map(all, ft_color(255,255,255, 255), 0);
			j++;
		}
		i++;
	}
}

void draw_line(t_all *all, int end_x, int end_y, int color)
{    
    int dy;
    int dx;
    int sx;
    int sy;
    int err;
    int e2;
    
    dx = abs(end_x - (int)all->player->ox);
    dy = abs(end_y - (int)all->player->oy);
    err = dx - dy;
    if (all->player->ox < end_x)
        sx = 1;
    else
        sx = -1;
    if (all->player->oy < end_y)
        sy = 1;
    else 
        sy = -1;
    while ((int)all->player->ox != end_x || (int)all->player->oy != end_y)
    {
        mlx_put_pixel(all->cub->img, (int)all->player->ox, (int)all->player->oy, color);
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            all->player->ox += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            all->player->oy += sy;
        }
    }
    mlx_put_pixel(all->cub->img, end_x, end_y, color);
}

void	player_angle(t_all *all)
{
	if(all->player->pl_dir == 'N')
		all->player->angle = (3 * M_PI) / 2 ;
	else if(all->player->pl_dir == 'S')
		all->player->angle = M_PI / 2;
	else if(all->player->pl_dir == 'E')
		all->player->angle = 0;
	else if(all->player->pl_dir == 'W')
		all->player->angle = M_PI;
}

int beetwen(t_all *all, float yend, float xend)
{
	if ((all->cub->lines[((int)yend + 1) / q_size][(int)xend / q_size] == '1'
		&& all->cub->lines[(int)yend / q_size][((int)xend + 1) / q_size] == '1')
		|| (all->cub->lines[((int)yend + 1) / q_size][(int)xend / q_size] == '1'
		&& all->cub->lines[(int)yend / q_size][((int)xend - 1) / q_size] == '1')
		|| (all->cub->lines[((int)yend - 1) / q_size][(int)xend / q_size] == '1'
		&& all->cub->lines[(int)yend / q_size][((int)xend - 1) / q_size] == '1')
		|| (all->cub->lines[((int)yend - 1) / q_size][(int)xend / q_size] == '1'
		&& all->cub->lines[(int)yend / q_size][((int)xend + 1) / q_size] == '1'))
		return (0);
	return (1);
}

void	hor_point(t_all *all, float angle)
{
	float yend;
	float xend;
	float	xstep;
	float ystep;
	all->player->ox = (all->player->x);
	all->player->oy = (all->player->y);
	if (angle > 0 && angle < M_PI)
	{
		yend = floor(all->player->oy / q_size) *  q_size + q_size;
		ystep = q_size;
	}
	if(!(angle > 0 && angle < M_PI))
	{
		yend = floor(all->player->oy / q_size) *  q_size - 0.0001f;
		ystep = -1 * q_size;
	}
	xend = all->player->ox + ((yend - all->player->oy) / tan(angle));
	xstep = ystep / tan(angle);
	while (((xend) >= 0 && (yend) >= 0) && (xend / q_size) < (all->cub->width / q_size)
			&& (yend / q_size) < (all->cub->height / q_size)
			&& all->cub->lines[(int)yend / q_size]
			&& (xend / q_size) < (int)ft_strlen(all->cub->lines[(int)yend / q_size], 0)
			&& all->cub->lines[(int)yend / q_size][(int)xend / q_size] != ' '
			&& all->cub->lines[(int)yend / q_size][(int)xend / q_size] != '1'
			&& beetwen(all, yend, xend))
	{
		xend += xstep;
		yend += ystep;
	}
	// if (xend < 0)
	// 	xend = 0;
	all->hor_p_x = xend;
	all->hor_p_y = yend;
}

void	ver_point(t_all *all, float angle)
{
	float yend;
	float xend;
	float	xstep;
	float ystep;
	all->player->ox = all->player->x;
	all->player->oy = all->player->y;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI))
	{
		xend = floor(all->player->ox / q_size) *  q_size - 0.0001f;
		xstep = -1 * q_size; 
	}
	if(angle < 0.5 * M_PI || angle > 1.5 * M_PI)
	{
		xend = floor(all->player->ox / q_size) *  q_size + q_size ;
		xstep = q_size;
	}
	yend = all->player->oy + ((xend - all->player->ox) * tan(angle));
	ystep = xstep * tan(angle);
	while (((xend / q_size) >= 0 && (yend / q_size) >= 0) && (xend / q_size) < (all->cub->width / q_size)
			&& (yend / q_size) < (all->cub->height / q_size)
			&& all->cub->lines[(int)yend / q_size]
			&& (xend / q_size) < (int)ft_strlen(all->cub->lines[(int)yend / q_size], 0)
			&& all->cub->lines[(int)yend / q_size][(int)xend / q_size] != ' '
			&& all->cub->lines[(int)yend / q_size][(int)xend / q_size] != '1'
			&& beetwen(all, yend, xend))
	{
		xend += xstep;
		yend += ystep;
	}
	all->ver_p_x = xend;
	// if (yend < 0)
	// 	yend = 0;
	all->ver_p_y = yend;
}

int point_ch(t_all *all , float san, float can)
{
	all->player->a[1] = all->player->x;
	all->player->a[0] = all->player->y;
	all->player->b[1] = (all->player->x + 3);
	all->player->b[0] = all->player->y;
	all->player->c[1] = (all->player->x + 3);
	all->player->c[0] = (all->player->y + 3);
	all->player->d[1] = all->player->x;
	all->player->d[0] = (all->player->y + 3);
	if (all->cub->lines[(int)((all->player->a[0] + san)) / q_size][(int)((all->player->a[1]+ can)) / q_size] == '1'
		|| all->cub->lines[(int)((all->player->b[0] + san)) / q_size][(int)((all->player->b[1]+ can)) / q_size] == '1'
		|| all->cub->lines[(int)((all->player->c[0] + san)) / q_size][(int)((all->player->c[1]+ can)) / q_size] == '1'
		|| all->cub->lines[(int)((all->player->d[0] + san)) / q_size][(int)((all->player->d[1]+ can)) / q_size] == '1')
		return (1);
	return (0);
}

int	dest_vita(t_all *all)
{
	int d_hor;
	int d_ver;
	d_hor = sqrt(pow(all->hor_p_x - all->player->ox, 2) + pow(all->hor_p_y - all->player->oy, 2));
	d_ver = sqrt(pow(all->ver_p_x - all->player->ox, 2) + pow(all->ver_p_y - all->player->oy, 2));

	if (d_hor < d_ver)
		return (1);
	else if (d_ver < d_hor)
		return (0);
	return (3);
}

void ft_catch(void *d)
{
	t_all *all;
	

	all = d;
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_LEFT))
	{
		all->player->angle -= 0.1;
		if (all->player->angle < 0)
			all->player->angle += M_PI * 2; 
	}
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_RIGHT))
	{
		all->player->angle += 0.1;
		if (all->player->angle >= M_PI * 2)
			all->player->angle -= (M_PI * 2);
	}
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_W))
    {
        if (!point_ch(all, sin(all->player->angle) * pl_speed, cos(all->player->angle) * pl_speed))
        {
            all->player->y += (sin(all->player->angle) * pl_speed);
            all->player->x += (cos(all->player->angle) * pl_speed);
        }
    }
    if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_S))
    {
        if (!point_ch(all, -sin(all->player->angle) * pl_speed, -cos(all->player->angle) * pl_speed))
        {
            all->player->y -= (sin(all->player->angle) * pl_speed);
            all->player->x -= (cos(all->player->angle) * pl_speed);
        }
    }
    if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_D))
    {
        if (!point_ch(all, sin(all->player->angle + (M_PI / 2)) * pl_speed, cos(all->player->angle + (M_PI / 2)) * pl_speed))
        {
            all->player->y += sin(all->player->angle + (M_PI / 2)) * pl_speed;
            all->player->x += cos(all->player->angle + (M_PI / 2)) * pl_speed;
        }
    }
    if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_A))
    {
        if (!point_ch(all, sin(all->player->angle - (M_PI / 2)) * pl_speed, cos(all->player->angle - (M_PI / 2)) * pl_speed))
        {
            all->player->y += sin(all->player->angle - (M_PI / 2)) * pl_speed;
            all->player->x += cos(all->player->angle - (M_PI / 2)) * pl_speed;
        }
    }
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_ESCAPE))
		exit (0);
	ft_draw_map(all);
	all->ray_angle = all->player->angle - deg_to_rad (30);
	if (all->ray_angle < 0)
		all->ray_angle += 2 * M_PI;
	else if (all->ray_angle >= 2 * M_PI)
		all->ray_angle -= 2 * M_PI;
	float xend, yend = 0;//////////
	int numray = 0;
	while (numray <= all->cub->width)
	{
		hor_point(all, all->ray_angle);
		ver_point(all, all->ray_angle);
		if (dest_vita(all) == 1)
		{
			xend = all->hor_p_x;
			yend = all->hor_p_y;
			draw_line(all, xend, yend, ft_color(255, 0, 0, 255));
		}
		else if ((dest_vita(all) == 0))
		{
			xend = all->ver_p_x;
			yend = all->ver_p_y;
			draw_line(all, xend, yend, ft_color(0, 255, 0, 255));
		}
		else
		{
			xend = all->ver_p_x;
			yend = all->ver_p_y;
			draw_line(all, xend, yend, ft_color(0, 0, 255, 255));
		}
		all->ray_angle += deg_to_rad(60) / all->cub->width;
		if (all->ray_angle < 0)
			all->ray_angle += 2 * M_PI;
		else if (all->ray_angle >= 2 * M_PI)
			all->ray_angle -= 2 * M_PI;
		numray++;
	}
	drow_player(all, ft_color(251,65,88, 255));
} 

void ft_draw(t_all *all)
{   
	all->cub->width = long_line(all->cub) * q_size;
	all->cub->height = h_map(all->cub) * q_size;
    all->cub->mlx_ptr = mlx_init(all->cub->width, all->cub->height, "rase mohmaad", true);
	all->cub->img = mlx_new_image(all->cub->mlx_ptr, all->cub->width, all->cub->height);
	mlx_image_to_window(all->cub->mlx_ptr, all->cub->img, 0, 0);
	ft_draw_map(all);///
	player_angle(all);
	// draw_line(all, all->player->angle);////
	drow_player(all, ft_color(251,65,88, 255));
	mlx_loop_hook(all->cub->mlx_ptr, ft_catch, all);
	mlx_loop(all->cub->mlx_ptr);
}
