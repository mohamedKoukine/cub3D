/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:54:42 by aelbouab          #+#    #+#             */
/*   Updated: 2024/10/04 09:25:53 by aelbouab         ###   ########.fr       */
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

// ft_right(int x, int y, t_data *d)
// {
// 	printf("right\n");

// }
// ft_lef(int x, int y, t_data *d)
// {
// 	printf("left\n");
// }
// ft_down(int x, int y, t_data *d)
// {
// 	printf("down");
// }
// ft_up(int x, int y, t_data *d)
// {
// 	printf("up\n");
// }

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
	x = all->player->x;
	while(i <= q_size / 2)
	{
		j = 0;
		all->player->x = x;
		while (j <= q_size / 2)
		{
				mlx_put_pixel(all->cub->img, all->player->x, all->player->y, color);
			j++;
			all->player->x++;
		}
		all->player->y++;
		i++;
	}
	all->player->y = y;
	all->player->x = x;
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

void draw_line_1(t_all *all, int end_x, int end_y, int color)
{    
    int dy;
    int dx;
    int sx;
    int sy;
    int err;
    int e2;(void)color;
    
    dx = abs(end_x - all->player->ox);
    dy = abs(end_y - all->player->oy);
    err = dx - dy;
    if (all->player->ox < end_x)
        sx = 1;
    else
        sx = -1;
    if (all->player->oy < end_y)
        sy = 1;
    else 
        sy = -1;
    while (all->player->ox != end_x || all->player->oy != end_y)
    {
        mlx_put_pixel(all->cub->img, all->player->ox, all->player->oy, color);
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

void	draw_line(t_all *all)
{
	int xend;
	int yend;
	all->player->ox = ((all->player->x + (q_size / 4)));
	all->player->oy = ((all->player->y + (q_size / 4)));
	xend = all->player->ox + (cos(all->player->angle) * 35);
	yend = all->player->oy + (sin(all->player->angle) * 35);
	// printf(" = %d\n", );
	draw_line_1(all, xend, yend, ft_color(0, 0, 0, 255));
	// while (i < 50)
	// {
	// 	mlx_put_pixel(all->cub->img, all->player->oy, all->player->ox, ft_color(0 , 0 , 0 , 255));
	// 	if (all->player->pl_dir == 'N')
	// 		all->player->ox += cos(90);
	// 	else if (all->player->pl_dir == 'E')
	// 		all->player->oy += cos(0);
	// 	else if (all->player->pl_dir == 'S')
	// 		all->player->ox += cos(0);
	// 	else if (all->player->pl_dir == 'W')
	// 		all->player->oy += cos(90);
	// 	i++;
	// }
}
//san =   sin(all->player->angle) * 2      can = cos(all->player->angle) * 2
int point_ch(t_all *all , float san, float can)
{
	all->player->a[1] = all->player->x;
	all->player->a[0] = all->player->y;
	all->player->b[1] = (all->player->x + q_size / 2);
	all->player->b[0] = all->player->y;
	all->player->c[1] = (all->player->x + q_size / 2);
	all->player->c[0] = (all->player->y + q_size / 2);
	all->player->d[1] = all->player->x;
	all->player->d[0] = (all->player->y + q_size / 2);
	if (all->cub->lines[(int)((all->player->a[0] + san)) / q_size][(int)((all->player->a[1]+ can)) / q_size] == '1'
		|| all->cub->lines[(int)((all->player->b[0] + san)) / q_size][(int)((all->player->b[1]+ can)) / q_size] == '1'
		|| all->cub->lines[(int)((all->player->c[0] + san)) / q_size][(int)((all->player->c[1]+ can)) / q_size] == '1'
		|| all->cub->lines[(int)((all->player->d[0] + san)) / q_size][(int)((all->player->d[1]+ can)) / q_size] == '1')
		return (1);
	return (0);
}

void ft_catch(void *d)
{
	t_all *all;

	all = d;
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_LEFT))
	{
		all->player->angle -= 0.1;
		if (all->player->angle == 0)
			all->player->angle += M_PI * 2; 
	}
	else if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_RIGHT))
	{
		all->player->angle += 0.1;
		if (all->player->angle == M_PI * 2)
			all->player->angle -= M_PI * 2;
	}
	else if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_W))
	{
		if (!point_ch(all, sin(all->player->angle) * 2, cos(all->player->angle) * 2))
		{
			all->player->y += sin(all->player->angle) * 2;
			all->player->x += cos(all->player->angle) * 2;
		}
	}
	else if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_S))
	{
		if (!point_ch(all, (sin(all->player->angle  * -1) * 2), (cos(all->player->angle  * -1) * 2)))
		{
			all->player->y += sin(all->player->angle - M_PI - 0.1) * 2;
			all->player->x += cos(all->player->angle - M_PI - 0.1) * 2;
		}
	}
	else if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_D))
	{
		if (!point_ch(all, sin(all->player->angle + (M_PI / 2)) * 2, cos(all->player->angle + (M_PI / 2)) * 2))
		{
			all->player->y += sin(all->player->angle + (M_PI / 2)) * 2;
			all->player->x += cos(all->player->angle + (M_PI / 2)) * 2;
		}
	}
	else if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_A))
	{
		if (!point_ch(all, sin((M_PI / 2) - all->player->angle) * 2, cos((M_PI / 2) - all->player->angle) * 2))
		{
			all->player->y += sin(all->player->angle - (M_PI / 2) - 0.1) * 2;
			all->player->x += cos(all->player->angle - (M_PI / 2) - 0.1) * 2;
		}
	}
		// if ()
		// {
			// all->player->y -= sin(all->player->angle);
			// all->player->x += cos(all->player->angle);
		// }
	// else if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_S))
	// {
	// 	all->player->y += 10;
	// }
	ft_draw_map(all);
	draw_line(all);
	drow_player(all, ft_color(251,65,88, 255));
} 

void ft_draw(t_all *all)
{   
    all->cub->mlx_ptr = mlx_init(long_line(all->cub) * q_size, h_map(all->cub) * q_size, "rase mohmaad", true);
	all->cub->img = mlx_new_image(all->cub->mlx_ptr, long_line(all->cub) * q_size, h_map(all->cub) * q_size);
	mlx_image_to_window(all->cub->mlx_ptr, all->cub->img, 0, 0);
	ft_draw_map(all);///
	player_angle(all);
	draw_line(all);////
	drow_player(all, ft_color(251,65,88, 255));
	mlx_loop_hook(all->cub->mlx_ptr, ft_catch, all);
	mlx_loop(all->cub->mlx_ptr);
}
