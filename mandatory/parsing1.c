/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:22:45 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/09 15:53:50 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	slide_in(t_all *all, float y, float x)
{
	if (!point_ch(all, y, 0))
		all->player->y += y;
	if (!point_ch(all, 0, x))
		all->player->x += x;
}

void	check_valid_file(t_cub *cub, int i, int j)
{
	cub->f[0] = 0;
	cub->f[1] = 0;
	cub->f[2] = 0;
	cub->f[3] = 0;
	cub->f[4] = 0;
	cub->f[5] = 0;
	while (cub->d[++i])
		cub->d[i] = ft_strtrim(cub->d[i], " ");
	j = -1;
	while (cub->d[++j])
	{
		i = 0;
		if (cub->d[j][i])
			check_valid_con(cub, j, i);
		if (cub->f[0] == 1 && cub->f[1] == 1 && cub->f[2] == 1
			&& cub->f[3] == 1 && cub->f[4] == 1 && cub->f[5] == 1)
			break ;
		else if (cub->f[0] > 1 || cub->f[1] > 1 || cub->f[2] > 1
			|| cub->f[3] > 1 || cub->f[4] > 1 || cub->f[5] > 1)
			ft_error("map not valide8", cub, 1);
	}
}

int	find_i(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cub->l[++i])
	{
		if ((cub->l[i] == 'N' && cub->l[i + 1] == 'O')
			|| (cub->l[i] == 'S' && cub->l[i + 1] == 'O')
			|| (cub->l[i] == 'E' && cub->l[i + 1] == 'A')
			|| (cub->l[i] == 'F' && cub->l[i + 1] == ' ')
			|| (cub->l[i] == 'C' && cub->l[i + 1] == ' ')
			|| (cub->l[i] == 'W' && cub->l[i + 1] == 'E'))
		{
			while (cub->l[i] && cub->l[i] != 10)
				i++;
			j++;
		}
		if (j == 6)
			return (i);
	}
	return (i);
}
