/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:54:42 by aelbouab          #+#    #+#             */
/*   Updated: 2024/09/27 15:01:12 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_map(int x, int y, void *image)
{
	int i;
	int j;
	int sy;
	
	i = 0;
	sy = y;
	while(i <= q_size)
	{
		j = 0;
		y = sy;
		while (j <= q_size)
		{
			mlx_put_pixel(image, y, x, 0xFF00FF);
			j++;
			y++;
		}
		x++;
		i++;
	}
}

size_t	long_line(t_data *data)
{
	int		i;
	size_t	j;
	
	i = 0;
	j = 0;
	while (data->lines[i])
	{
		if (j < ft_strlen(data->lines[i], 1))
			j = ft_strlen(data->lines[i], 1);
		i++;
	}
	return (j);
}

int h_map(t_data *data)
{
	int i;

	i= 0;
	while (data->lines[i])
		i++;
	return (i);
}

void ft_draw(t_data *data)
{
    void	*mlx_ptr;
	void	*image;
    int		i;
	int		j;

    i = 0;
	j = 0;    
    mlx_ptr = mlx_init(long_line(data) * q_size, h_map(data) * q_size, "MLX42", true);
	image = mlx_new_image(mlx_ptr, long_line(data) * q_size, h_map(data) * q_size);
	mlx_image_to_window(mlx_ptr, image, 0, 0);
	while (data->lines[i])
	{
		j = 0;
		while (data->lines[i][j])
		{
			if (data->lines[i][j] == '1')
				draw_map(i * q_size, j * q_size, image);
			j++;
		}
		i++;
	}
	mlx_loop(mlx_ptr);
}
