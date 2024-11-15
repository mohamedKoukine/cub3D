/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cub3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:49:47 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/15 16:25:40 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_CUB3D_H
# define B_CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/MLX42.h"

typedef struct s_cub
{
	int			f[6];
	char		*l;
	char		**d;
	int			x;
	int			y;
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*img;
	char		**lines;
	int			minix;
	int			miniy;
	char		*paths[6];
	int			ff[3];
	int			c[3];
	mlx_image_t	*texture[5];
	int32_t		pixel;
	int32_t		pixel1;
	int32_t		pixel2;
	int32_t		pixel3;
}		t_cub;

typedef struct s_player
{
	float		x;
	float		y;
	float		x_mini;
	float		y_mini;
	float		ox;
	float		oy;
	float		a[2];
	float		b[2];
	float		c[2];
	float		d[2];
	float		angle;
	char		pl_dir;
}		t_player;

typedef struct s_mouse
{
	int	x;
	int	y;
}		t_mouse;

typedef struct s_all
{
	int					res_w;
	int					res_h;
	float				ray_angle;
	int					ray_dist;
	int					x;
	float				hor_p_x;
	float				ver_p_x;
	float				hor_p_y;
	float				ver_p_y;
	int					flag_door;
	struct s_player		*player;
	struct s_cub		*cub;
	struct s_mouse		*mouse;
}		t_all;

char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjo_or_cat(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str, int flag);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
void	char_check(char *line);
void	player_nb(char *line);
void	skep_nl(char *line);
void	freeall(char **ptr);
void	empty_sp(char **map, t_cub *cub);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
void	ft_draw(t_all *all);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
void	ft_error(char *s, t_cub *cub, int index);
void	check_number(t_cub *cub, int j, int i, int l);
int		check_f_c(t_cub *cub, int i, int j, int k);
void	check_valid_con(t_cub *cub, int j, int i);
void	check_valid_file(t_cub *cub, int i, int j);
int		find_i(t_cub *cub);
void	parsing(char *s, t_cub *cub);
int		ft_color(int r, int g, int b, int a);
void	draw_map(t_all *all, int color, int type);
size_t	long_line(t_cub *cub);
int		h_map(t_cub *cub);
double	deg_to_rad(double an);
void	draw_player(t_all *all, int color);
void	draw_mp(t_all *all, char c);
void	ft_draw_map(t_all *all);
void	ft_draw_map(t_all *all);
void	player_angle(t_all *all);
int		beetwen(t_all *all, float yend, float xend);
void	hor_point(t_all *all, float angle);
int		point_ch(t_all *all, float san, float can);
void	ver_point(t_all *all, float angle);
float	dest_vita1(t_all *all);
float	dest_vita2(t_all *all);
void	draw_rm(t_all *all, float wall_h);
void	draw_fc(t_all *all);
void	draw_texture(t_all *all, float wall_h, int i);
void	draw_3d(t_all *all);
void	ft_do(t_all *all);
void	fill_fc(char *s, t_cub *cub, int index);
void	key_rotation(t_all *all);
void	check_door(t_all *all);
void	draw_minimap(t_all *all);
void	close_door(t_all *all);
void	draw_line(t_all *all);
void	slide_in(t_all *all, float y, float x);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

# define Q_SIZE  500
# define P_S 100

#endif