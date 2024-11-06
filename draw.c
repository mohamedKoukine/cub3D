/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:03:18 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/06 13:49:55 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotation(t_all *all)
{
	int		m_x;
	int		m_y;

	mlx_get_mouse_pos(all->cub->mlx_ptr, &m_x, &m_y);
	if (m_x < all->mouse->x)
		all->player->angle -= 0.001 * (all->mouse->x - m_x);
	if (m_x > all->mouse->x)
		all->player->angle += 0.001 * (m_x - all->mouse->x);
	if (all->player->angle >= M_PI * 2)
			all->player->angle -= (M_PI * 2);	
	if (all->player->angle < 0)
			all->player->angle += M_PI * 2; 	
	mlx_set_mouse_pos(all->cub->mlx_ptr, all->res_w / 2, all->res_h / 2);
	all->mouse->x = all->res_w / 2;
	all->mouse->y = all->res_h / 2;
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
 
void draw_line(t_all *all)
{
	int i;
	float x;
	float y;

	i = 0;
	x = 102;
	y = 102;
	while (i <= 10)
	{
		mlx_put_pixel(all->cub->img, x, y, ft_color(251,65,88, 255));
		x += cos(all->player->angle);
		y += sin(all->player->angle);
		i++;
	}
	
}

void	draw_out(t_all *all, int color)
{
	int i;
	int j;

	i = 0;
	while (i <= 210)
	{
		j = 0;
		while (j <= 210)
		{
			if ((i < 9) + (j < 9) + (i > 201) + (j > 201))
				mlx_put_pixel(all->cub->img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_all *all)
{
	int i;
	int j;

	i = 0;
	draw_line(all);
	while (all->cub->lines[i])
	{
		j = 0;
		while ((size_t)j < ft_strlen(all->cub->lines[i], 0))
		{
			all->cub->x =  (j * 10) + ((200 / 2) - all->player->x_mini);
			all->cub->y =  (i * 10) + ((200 / 2) - all->player->y_mini);
			draw_mp(all, all->cub->lines[i][j]);
			j++;
		}
		i++;
	}
	draw_out(all, ft_color(0,0,0, 255));
	draw_player(all, ft_color(251,65,88, 255));
}

void	check_door (t_all *all)
{
	if (all->cub->lines[(int)all->player->y / Q_SIZE][(int)all->player->x / Q_SIZE + 1] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE][(int)all->player->x / Q_SIZE + 1] = 'd';
	if (all->cub->lines[(int)all->player->y / Q_SIZE - 1][(int)all->player->x / Q_SIZE + 1] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE - 1][(int)all->player->x / Q_SIZE + 1] = 'd';
	if (all->cub->lines[(int)all->player->y / Q_SIZE + 1][(int)all->player->x / Q_SIZE + 1] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE + 1][(int)all->player->x / Q_SIZE + 1] = 'd';
	if (all->cub->lines[(int)all->player->y / Q_SIZE][(int)all->player->x / Q_SIZE - 1] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE][(int)all->player->x / Q_SIZE - 1] = 'd';
	if (all->cub->lines[(int)all->player->y / Q_SIZE + 1][(int)all->player->x / Q_SIZE] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE + 1][(int)all->player->x / Q_SIZE] = 'd';
	if (all->cub->lines[(int)all->player->y / Q_SIZE + 1][(int)all->player->x / Q_SIZE - 1] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE + 1][(int)all->player->x / Q_SIZE - 1] = 'd';
	if (all->cub->lines[(int)all->player->y / Q_SIZE - 1][(int)all->player->x / Q_SIZE] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE - 1][(int)all->player->x / Q_SIZE] = 'd';
	if (all->cub->lines[(int)all->player->y / Q_SIZE - 1][(int)all->player->x / Q_SIZE - 1] == 'D')
		all->cub->lines[(int)all->player->y / Q_SIZE - 1][(int)all->player->x / Q_SIZE - 1] = 'd';
}


void	ft_catch(void *d)
{
	t_all	*all;
	int		i;
	int		j;

	all = d;
	j = -1;
	rotation(all);
	moves (all, 0, 0);
	if (mlx_is_key_down(all->cub->mlx_ptr, MLX_KEY_ESCAPE))
		exit (0);
	check_door(all);
	ft_draw_map(all);
	draw_fc(all);
	all->ray_angle = all->player->angle - deg_to_rad (30);
	if (all->ray_angle < 0)
		all->ray_angle += 2 * M_PI;
	else if (all->ray_angle >= 2 * M_PI)
		all->ray_angle -= 2 * M_PI;
	draw_3d (all);
	draw_minimap (all);
	while (all->cub->lines[++j])
	{
		i = -1;
		while (all->cub->lines[j][++i])
			if (all->cub->lines[j][i] == 'd')
				all->cub->lines[j][i] = 'D';
	}
}

void	fill_img(t_cub *cub)
{
	mlx_texture_t	*img_e;
	mlx_texture_t	*img_w;
	mlx_texture_t	*img_n;
	mlx_texture_t	*img_s;
	mlx_texture_t	*img_d_c;
	// mlx_texture_t	*img_d_o;

	img_e = mlx_load_png(cub->paths[0]);
	if (!img_e)
		ft_error("error image1", cub);
	cub->texture[0] = mlx_texture_to_image(cub->mlx_ptr, img_e);
	img_w = mlx_load_png(cub->paths[1]);
	if (!img_w)
		ft_error("error image2", cub);
	cub->texture[1] = mlx_texture_to_image(cub->mlx_ptr, img_w);
	img_n = mlx_load_png(cub->paths[2]);
	if (!img_n)
		ft_error("error image3", cub);
	cub->texture[2] = mlx_texture_to_image(cub->mlx_ptr, img_n);
	img_s = mlx_load_png(cub->paths[3]);
	if (!img_s)
		ft_error("error image4", cub);
	cub->texture[3] = mlx_texture_to_image(cub->mlx_ptr, img_s);
	
	img_d_c = mlx_load_png(cub->paths[4]);
	if (!img_d_c)
		ft_error("error image5", cub);
	cub->texture[4] = mlx_texture_to_image(cub->mlx_ptr, img_d_c);

	if (!cub->texture[0] || !cub->texture[1]
		|| !cub->texture[2] || !cub->texture[3] || !cub->texture[4])
		ft_error("error image7", cub);
}

void	ft_draw(t_all *all)
{
	all->cub->width = long_line(all->cub) * Q_SIZE;
	all->cub->height = h_map(all->cub) * Q_SIZE;
	all->x = 0;
	all->jump = all->cub->height / 2;
	all->res_w = 1570;
	all->res_h = 800;
	all->cub->mlx_ptr = mlx_init(all->res_w, all->res_h, "rase mohmaad", true);
	all->cub->img = mlx_new_image(all->cub->mlx_ptr, all->res_w, all->res_h);
	fill_img(all->cub);
	mlx_image_to_window(all->cub->mlx_ptr, all->cub->img, 0, 0);
	ft_draw_map(all);
	draw_fc(all);
	player_angle(all);
	draw_line(all);
	mlx_set_mouse_pos(all->cub->mlx_ptr, all->res_w / 2, all->res_h / 2);
	all->mouse->x = all->res_w / 2;
	all->mouse->y = all->res_h / 2;
	mlx_set_cursor_mode(all->cub->mlx_ptr, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(all->cub->mlx_ptr, ft_catch, all);
	mlx_loop(all->cub->mlx_ptr);
}
