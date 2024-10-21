/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:54:42 by aelbouab          #+#    #+#             */
/*   Updated: 2024/10/21 11:09:16 by mkaoukin         ###   ########.fr       */
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

void	draw_player(t_all *all, int color)
{
	int i;
	int j;
	int y;
	int x;
	
	i = 0;
	y = all->player->y;
	x = all->player->x - 1;
	while(i <= 7)
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
		draw_map(all, ft_color(17,0,199, 255), 1);
	else if (c == '0')
		draw_map(all, ft_color(255,255,255, 255), 0);
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
			draw_mp(all, all->cub->lines[i][j]);
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
	all->player->ox = (all->player->x) + 3;
	all->player->oy = (all->player->y) + 3;
	if (angle > 0 && angle < M_PI)
	{
		yend = floor(all->player->oy / q_size) *  q_size + q_size;
		ystep = q_size;
	}
	if(!(angle > 0 && angle < M_PI))
	{
		yend = floor(all->player->oy / q_size) *  q_size - 0.001f;
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
	if (xend < 0)
		xend = 0;
	all->hor_p_x = xend;
	all->hor_p_y = yend;
}

void	ver_point(t_all *all, float angle)
{
	float yend;
	float xend;
	float	xstep;
	float ystep;
	all->player->ox = all->player->x + 3;
	all->player->oy = all->player->y + 3;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI))
	{
		xend = floor(all->player->ox / q_size) *  q_size - 0.001f;
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
	if (yend < 0)
		yend = 0;
	all->ver_p_y = yend;
}

int point_ch(t_all *all , float san, float can)
{
	all->player->a[1] = (all->player->x + can) / q_size;
	all->player->a[0] = (all->player->y + san) / q_size;
	all->player->b[1] = ((all->player->x + 6) + can) / q_size;
	all->player->b[0] = (all->player->y + san) / q_size;
	all->player->c[1] = ((all->player->x + 6) + can) / q_size;
	all->player->c[0] = ((all->player->y + 6)+ san) / q_size;
	all->player->d[1] = (all->player->x + can) / q_size;
	all->player->d[0] = ((all->player->y + 6)+ san) / q_size;
	if (!all->cub->lines[(int)all->player->a[0]]
		|| !all->cub->lines[(int)all->player->b[0]]
		|| !all->cub->lines[(int)all->player->c[0]]
		|| !all->cub->lines[(int)all->player->d[0]])
		return (1);
	if (all->cub->lines[(int)all->player->a[0] ][(int)all->player->a[1] ] == '1'
		|| all->cub->lines[(int)all->player->b[0] ][(int)all->player->b[1] ] == '1'
		|| all->cub->lines[(int)all->player->c[0] ][(int)all->player->c[1] ] == '1'
		|| all->cub->lines[(int)all->player->d[0] ][(int)all->player->d[1] ] == '1')
		return (1);
	return (0);
}
float	dest_vita1(t_all *all)
{
	float d_hor;
	float d_ver;
	d_hor = sqrt(pow(all->hor_p_x - all->player->ox, 2) + pow(all->hor_p_y - all->player->oy, 2));
	d_ver = sqrt(pow(all->ver_p_x - all->player->ox, 2) + pow(all->ver_p_y - all->player->oy, 2));
	if (d_hor < d_ver)
		return 1;
	return 0;
}
float	dest_vita2(t_all *all)
{
	float d_hor;
	float d_ver;
	d_hor = sqrt(pow(all->hor_p_x - all->player->ox, 2) + pow(all->hor_p_y - all->player->oy, 2));
	d_ver = sqrt(pow(all->ver_p_x - all->player->ox, 2) + pow(all->ver_p_y - all->player->oy, 2));
	if (d_hor < d_ver)
		return (d_hor * cos(all->player->angle - all->ray_angle));
	return (d_ver * cos(all->player->angle - all->ray_angle));
}

void draw_rm(t_all *all, float wall_h)
{
	int			y;
	int			i = 0;
	y = all->jump;
	while (i < wall_h / 2)
	{
		mlx_put_pixel(all->cub->img, all->x, y, ft_color(0, 0 , 255, 255));
		y--;
		i++;
	}
	y = all->jump;
	while (i < wall_h)
	{
		mlx_put_pixel(all->cub->img, all->x, y, ft_color(0, 0 , 255, 255));
		y++;
		i++;
	}
	if (all->x < all->cub->width)
		all->x++;
	else
		all->x = 0;
}

void draw_fc(t_all *all)
{
	int i= 0;
	int j= 0;
	while (i < all->cub->height)
	{
		j = 0;
		while (j < all->cub->width)
		{
			if (i < all->jump)
				mlx_put_pixel(all->cub->img, j, i, ft_color(0, 255 , 255, 255));
			else
				mlx_put_pixel(all->cub->img, j, i, ft_color(255, 255 , 255, 255));
			j++;
		}
		i++;
	}
	
}

void	draw_mini(t_all *all)
{
	float	xend;
	float	yend;
	int		numray;

	numray = 0;
	while (numray <= all->cub->width)
	{
		hor_point(all, all->ray_angle);
		ver_point(all, all->ray_angle);
		if (dest_vita1(all) == 1)
		{
			xend = all->hor_p_x;
			yend = all->hor_p_y;
			draw_line(all, xend, yend, ft_color(255, 0, 0, 255));
		}
		else
		{
			xend = all->ver_p_x;
			yend = all->ver_p_y;
			draw_line(all, xend, yend, ft_color(0, 255, 0, 255));
		}
		all->ray_angle += deg_to_rad(60) / all->cub->width;
		if (all->ray_angle < 0)
			all->ray_angle += 2 * M_PI;
		else if (all->ray_angle >= 2 * M_PI)
			all->ray_angle -= 2 * M_PI;
		numray++;
	}
	draw_player(all, ft_color(251,65,88, 255));
}


void	draw_texture(t_all *all, float wall_h)
{
	int			y;
	y = all->jump;
	int text_of_x;
	int text_of_y;

	int wall_top_px = (all->cub->height / 2) - ((int) wall_h / 2);
	int wall_bottom_px = (all->cub->height / 2) + ((int) wall_h / 2);


	
	// printf ("y   %d\n", wall_top_px);
	// printf ("wall_top_px   %d\n", wall_bottom_px);
	y = wall_top_px;
	if (dest_vita1(all))
		text_of_x = (((int) all->hor_p_x % q_size) * all->cub->texture->width / q_size) ;
	else
		text_of_x = (((int) all->ver_p_y % q_size) * all->cub->texture->width / q_size);


	while (y < wall_bottom_px)
	{
		text_of_y = (y - wall_top_px) * (float) all->cub->texture->height / (float) (wall_h);
		int	index = ((all->cub->texture->width * text_of_y) + text_of_x) * 4;
		int32_t pixel = all->cub->texture->pixels[index];
		int32_t pixel1 = all->cub->texture->pixels[index + 1];
		int32_t pixel2 = all->cub->texture->pixels[index + 2];
		int32_t pixel3 = all->cub->texture->pixels[index + 3];
		mlx_put_pixel(all->cub->img, all->x, y++, ft_color(pixel, pixel1, pixel2,pixel3));
	}
	

	// while (y < wall_bottom_px)
	// {
	// 	int top = y + (wall_h/ 2) - (all->cub->height / 2);
	// 	text_of_y = top * ((float)q_size / (float) wall_h);

	// 	// text_of_y = (y - wall_top_px) * (float) all->cub->texture->height / (float) wall_h;
	// 	uint32_t pixel = all->cub->texture->pixels[((q_size * text_of_y) + text_of_x) * 4];
	// 	uint32_t pixel1 = all->cub->texture->pixels[((q_size * text_of_y) + text_of_x) * 4 + 1];
	// 	uint32_t pixel2 = all->cub->texture->pixels[((q_size * text_of_y) + text_of_x) * 4 + 2];
	// 	uint32_t pixel3 = all->cub->texture->pixels[((q_size * text_of_y) + text_of_x) * 4 + 3];
	// 	mlx_put_pixel(all->cub->img, all->x, y++, ft_color(pixel, pixel1, pixel2,pixel3));
	// }
	// while (i < wall_h)
	// {
	// 	text_of_y = (y - wall_top_px) * ((float) all->cub->texture->height / (int) (wall_h));
	// 	unsigned int pixel = (all->cub->texture->width * text_of_y) + text_of_x;
	// 	// unsigned int b  = (pixel >> 16) & 0xFF;
    //     // unsigned int g = (pixel >> 8)  & 0xFF;
    //     // unsigned int r  = pixel & 0xFF;
	// 	// unsigned int color  = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	// 	mlx_put_pixel(all->cub->img, all->x, y, ft_color(pixel,pixel,pixel,pixel));
	// 	y++;
	// 	i++;
	// // }
	if (all->x < all->cub->width)
		all->x++;
	else
		all->x = 0;
}

void	draw_3d(t_all *all)
{
	float	wall_h;
	int		numray;
	float	dpp;

	dpp = (all->cub->width / 2) / tan(deg_to_rad(30));
	numray = 0;
	while (numray <= all->cub->width)
	{
		hor_point(all, all->ray_angle);
		ver_point(all, all->ray_angle);
		float res = dest_vita2(all);
		wall_h = (q_size / res) * dpp;
		if (wall_h >= all->cub->height)
			wall_h = all->cub->height;
		// draw_rm(all, wall_h);
		draw_texture(all, wall_h);
		all->ray_angle += deg_to_rad(60) / all->cub->width;
		if (all->ray_angle < 0)
			all->ray_angle += 2 * M_PI;
		else if (all->ray_angle >= 2 * M_PI)
			all->ray_angle -= 2 * M_PI;
		numray++;
	}
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
	draw_fc(all);
	all->ray_angle = all->player->angle - deg_to_rad (30);
	if (all->ray_angle < 0)
		all->ray_angle += 2 * M_PI;
	else if (all->ray_angle >= 2 * M_PI)
		all->ray_angle -= 2 * M_PI;
	draw_3d(all);
	// draw_mini(all);
} 


void ft_draw(t_all *all)
{   
	all->cub->width = long_line(all->cub) * q_size;
	all->cub->height = h_map(all->cub) * q_size;
	all->x = 0;
	all->jump = all->cub->height / 2;
    all->cub->mlx_ptr = mlx_init(all->cub->width, all->cub->height, "rase mohmaad", true);
	all->cub->img = mlx_new_image(all->cub->mlx_ptr, all->cub->width, all->cub->height);
	mlx_image_to_window(all->cub->mlx_ptr, all->cub->img, 0, 0);
	ft_draw_map(all);///
	draw_fc(all);
	player_angle(all);
	// draw_line(all, all->player->angle);////
	draw_player(all, ft_color(251,65,88, 255));
	mlx_texture_t *img = mlx_load_png("./images/5.png");
	all->cub->texture = mlx_texture_to_image(all->cub->mlx_ptr, img);
	mlx_loop_hook(all->cub->mlx_ptr, ft_catch, all);
	mlx_loop(all->cub->mlx_ptr);
}
