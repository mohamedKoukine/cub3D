/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:54:27 by aelbouab          #+#    #+#             */
/*   Updated: 2024/11/15 11:55:42 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_cub3D.h"

void	fill_paths(t_cub *cub, char *s, int l)
{
	int	i;

	i = 2;
	while (s[i] && s[i] == 32)
		i++;
	cub->paths[l] = &s[i];
}

void	fill_arg(t_cub *cub, int j)
{
	while (cub->d[++j])
	{
		if (cub->d[j][0] == 'E')
			fill_paths(cub, cub->d[j], 0);
		else if (cub->d[j][0] == 'W')
			fill_paths(cub, cub->d[j], 1);
		else if (cub->d[j][0] == 'N')
			fill_paths(cub, cub->d[j], 2);
		else if (cub->d[j][0] == 'S')
			fill_paths(cub, cub->d[j], 3);
		else if (cub->d[j][0] == 'C')
			fill_fc(cub->d[j], cub, 0);
		else if (cub->d[j][0] == 'F')
			fill_fc(cub->d[j], cub, 1);
	}
	cub->paths[4] = "./images/door.png";
	cub->paths[5] = NULL;
}

void	door_check(t_cub *cub, int i, int cp)
{
	int	j;

	while (cub->lines[++i])
	{
		j = -1;
		while (cub->lines[i][++j])
		{
			cp = 0;
			if (cub->lines[i][j] == 'D')
			{
				if (i * j == 0 || !cub->lines[i + 1] || !cub->lines[i][j + 1]
					|| ft_strlen(cub->lines[i + 1], 0) <= (size_t)j
					|| ft_strlen(cub->lines[i - 1], 0) <= (size_t)j)
					return (printf ("door not in best place\n")
						, freeall(cub->lines), exit(1));
				if ((cub->lines[i][j + 1] == '1' && cub->lines[i][j - 1] == '1')
					|| (cub->lines[i + 1][j] == '1'
					&& cub->lines[i - 1][j] == '1'))
					cp++;
				if (cp == 0)
					return (printf ("door not in best place\n")
						, freeall(cub->lines), exit(1));
			}
		}
	}
}

void	parsing1(t_cub *cub, char *tmp)
{
	cub->d = ft_split(cub->l, '\n');
	check_valid_file(cub, -1, -1);
	tmp = ft_strdup(&cub->l[find_i(cub)]);
	char_check(tmp);
	player_nb(tmp);
	skep_nl(tmp);
	empty_sp(ft_split(tmp, '\n'), cub);
	fill_arg(cub, -1);
	door_check(cub, -1, 0);
	free (tmp);
}

void	parsing(char *s, t_cub *cub)
{
	int		i;
	char	*tmp;

	cub->l = NULL;
	i = ft_strlen(s, 0);
	if (i - 4 > 0 && !ft_strcmp(&s[i - 4], ".cub"))
	{
		i = open (s, O_RDONLY);
		if (i == -1)
			ft_error("file is not valide", NULL, 1);
		tmp = get_next_line(i);
		while (tmp)
		{
			cub->l = ft_strjoin(cub->l, tmp);
			free (tmp);
			tmp = get_next_line(i);
		}
		close(i);
		parsing1(cub, tmp);
	}
	else
		ft_error("file name is not valide", NULL, 1);
}
