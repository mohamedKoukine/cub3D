/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:03:18 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/15 11:53:18 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotation(t_all *all)
{
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
}

void	moves(t_all *all, float x, float y)
{
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_W))
	{
		y = sin(all->player->angle) * P_S;
		x = cos(all->player->angle) * P_S;
		slide_in(all, y, x);
	}
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_S))
	{
		y = -sin(all->player->angle) * P_S;
		x = -cos(all->player->angle) * P_S;
		slide_in(all, y, x);
	}
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_D))
	{
		y = sin(all->player->angle + (M_PI / 2)) * P_S;
		x = cos(all->player->angle + (M_PI / 2)) * P_S;
		slide_in(all, y, x);
	}
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_A))
	{
		y = sin(all->player->angle - (M_PI / 2)) * P_S;
		x = cos(all->player->angle - (M_PI / 2)) * P_S;
		slide_in(all, y, x);
	}
}

void	ft_catch(void *d)
{
	t_all	*all;

	all = d;
	rotation(all);
	moves (all, 0, 0);
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_close_window(all->cub->mlx_ptr);
		ft_error ("", all->cub, 0);
	}
	ft_draw_map(all);
	draw_fc(all);
	all->ray_angle = all->player->angle - deg_to_rad (30);
	if (all->ray_angle < 0)
		all->ray_angle += 2 * M_PI;
	else if (all->ray_angle >= 2 * M_PI)
		all->ray_angle -= 2 * M_PI;
	draw_3d (all);
}

void	fill_img(t_cub *cub)
{
	mlx_texture_t	*img;

	img = mlx_load_png(cub->paths[0]);
	if (!img)
		ft_error("error image11", cub, 1);
	cub->texture[0] = mlx_texture_to_image(cub->mlx_ptr, img);
	mlx_delete_texture(img);
	img = mlx_load_png(cub->paths[1]);
	if (!img)
		ft_error("error image", cub, 1);
	cub->texture[1] = mlx_texture_to_image(cub->mlx_ptr, img);
	mlx_delete_texture(img);
	img = mlx_load_png(cub->paths[2]);
	if (!img)
		ft_error("error image", cub, 1);
	cub->texture[2] = mlx_texture_to_image(cub->mlx_ptr, img);
	mlx_delete_texture(img);
	img = mlx_load_png(cub->paths[3]);
	if (!img)
		ft_error("error image", cub, 1);
	cub->texture[3] = mlx_texture_to_image(cub->mlx_ptr, img);
	mlx_delete_texture(img);
	if (!cub->texture[0] || !cub->texture[1]
		|| !cub->texture[2] || !cub->texture[3])
		ft_error("error image", cub, 1);
}

void	ft_draw(t_all *all)
{
	all->cub->width = long_line(all->cub) * Q_SIZE;
	all->cub->height = h_map(all->cub) * Q_SIZE;
	all->res_w = 1250;
	all->res_h = 780;
	all->cub->mlx_ptr = mlx_init(all->res_w, all->res_h, "rase mohmaad", true);
	if (!all->cub->mlx_ptr)
		ft_error("error mlx_unit", all->cub, 1);
	all->cub->img = mlx_new_image(all->cub->mlx_ptr, all->res_w, all->res_h);
	if (!all->cub->img)
	{
		mlx_close_window(all->cub->mlx_ptr);
		ft_error("error mlx_new_image", all->cub, 1);
	}
	fill_img(all->cub);
	if (mlx_image_to_window(all->cub->mlx_ptr, all->cub->img, 0, 0))
	{
		mlx_close_window(all->cub->mlx_ptr);
		ft_error("mlx_image_to_window", all->cub, 1);
	}
	ft_draw_map(all);
	draw_fc(all);
	player_angle(all);
	mlx_loop_hook(all->cub->mlx_ptr, ft_catch, all);
	mlx_loop(all->cub->mlx_ptr);
}
