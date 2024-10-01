/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:49:47 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/09/30 17:06:18 by aelbouab         ###   ########.fr       */
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
	void	*mlx_ptr;
	int		img_width;
	int		img_height;
	char	**lines;
}		t_cub;

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
void	ft_draw(t_cub *cub);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif
#  define q_size 20

#endif