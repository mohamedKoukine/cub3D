/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:49:47 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/10/10 19:12:55 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/MLX42.h"

typedef struct s_cub
{
	int		f[6];
	char    *l;
    char    **d;
	int		x;
	int		y;
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*img;
	char	**lines;
}		t_cub;

typedef struct s_player
{
	float	x;
	float	y;
	float	ox;
	float	oy;
	int		a[2];
	int		b[2];
	int		c[2];
	int		d[2];
	float	angle;
	char	pl_dir;
}		t_player;

typedef struct s_all
{
	float			ray_angle;
	int				ray_dist;
	float				hor_p_x;
	float				ver_p_x;
	float				hor_p_y;
	float				ver_p_y;
	struct s_player *player;
	struct s_cub 	*cub;
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
void	ft_error(char *s, t_cub *cub);
void	check_number(t_cub *cub, int j, int i, int	l);
int		check_F_c(t_cub *cub, int i, int j, int k);
void	check_valid_con(t_cub *cub, int j, int i);
void	check_valid_file(t_cub *cub ,int i, int j);
int		find_i(t_cub *cub);
void	parsing(char *s, t_cub *cub);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif
#  define q_size 100
#  define pl_speed 4

#endif