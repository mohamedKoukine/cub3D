/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:54:42 by aelbouab          #+#    #+#             */
/*   Updated: 2024/10/01 11:45:16 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8  | a);
}

void	draw_map(int x, int y, void *image, int color, char type)
{
	int i;
	int j;
	int sy;
	int sx;
	
	i = 0;
	sy = y;
	sx = x;
	while(i <= q_size)
	{
		j = 0;
		y = sy;
		while (j <= q_size)
		{
			if (type == '1' && (y == sy || x == sx || j == q_size || i == q_size))
				mlx_put_pixel(image, y, x, ft_color (0, 0, 0, 255));
			else
				mlx_put_pixel(image, y, x, color);
			j++;
			y++;
		}
		x++;
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

void ft_catch(void *d)
{
	t_cub *cub;

	cub = d;
	/* position player */
	int i = -1;
	int j = -1;
	int x;
	int y;

	while(cub->lines[++j])
	{
		i = -1;
		while(cub->lines[j][++i])
		{
			if (cub->lines[j][i] == 'E')
			{
				x = i;
				y = j;
			}
		}
	}
	printf("x == %d\n", x);
	printf("y == %d\n", y);
	
	int an = 90;
	printf("%f\n", cos(deg_to_rad(an)));
	printf("%f\n", sin(deg_to_rad(an)));
	// if (mlx_is_key_down(cub->mlx_ptr, MLX_KEY_LEFT))
	// 	ft_left(x, y, cub);
	// if (mlx_is_key_down(cub->mlx_ptr, MLX_KEY_RIGHT))
	// 	ft_right(x, y, cub);
	// if (mlx_is_key_down(cub->mlx_ptr, MLX_KEY_DOWN))
	// 	ft_down(x, y, cub);
	// if (mlx_is_key_down(cub->mlx_ptr, MLX_KEY_UP))
	// 	ft_up(x, y, cub);

	/**/
	// return (0);
} 

void ft_draw(t_cub *cub)
{
    void	*mlx_ptr;
	void	*image;
    int		i;
	int		j;

    i = 0;
	j = 0;    
    mlx_ptr = mlx_init(long_line(cub) * q_size, h_map(cub) * q_size, "rase mohmaad", true);
	image = mlx_new_image(mlx_ptr, long_line(cub) * q_size, h_map(cub) * q_size);
	mlx_image_to_window(mlx_ptr, image, 0, 0);
	while (cub->lines[i])
	{
		j = 0;
		while (cub->lines[i][j])
		{
			if (cub->lines[i][j] == '1')
				draw_map(i * q_size, j * q_size, image, ft_color(17,0,199, 255), cub->lines[i][j]);
			else if (cub->lines[i][j] == '0' || cub->lines[i][j] == 'E')
				draw_map(i * q_size, j * q_size, image, ft_color(255,255,255, 255), cub->lines[i][j]);
			j++;
		}
		i++;
	}
	// mlx_loop_hook(mlx_ptr, ft_catch, cub);
	mlx_loop(mlx_ptr);
}
