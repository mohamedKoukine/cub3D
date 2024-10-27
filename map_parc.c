/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:23:05 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/10/27 10:48:02 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	char_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\n')
		{
			printf ("map need to include : 0 for an empty space,"
				"1 for a wall, and N,S,E or W for the player\n");
			free(line);
			exit(1);
		}
		i++;
	}
}

void	player_nb(char *line)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'W')
			cp++;
		i++;
	}
	if (cp != 1)
	{
		free(line);
		if (cp == 0)
			printf ("“Where Is Messi?”\n");
		else
			printf ("more than one player in map\n");
		exit(1);
	}
}

void	skep_nl(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '\n' || line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
		{
			printf ("empty line in map\n");
			free(line);
			exit(1);
		}
		i++;
	}
}

void	freeall(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free (ptr[i]);
		i++;
	}
	free(ptr);
}

void	empty_sp(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'E' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'W')
			{
				if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1]
					|| map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
					return (printf ("empty space in map\n"), freeall(map)
						, exit(1));
				if (ft_strlen(map[i + 1], 0) <= (size_t)j
					|| ft_strlen(map[i - 1], 0) <= (size_t)j
					|| map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					return (printf ("empty space in map\n"), freeall(map)
						, exit(1));
			}
		}
	}
	cub->lines = map;
}
