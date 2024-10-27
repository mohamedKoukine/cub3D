/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:54:27 by aelbouab          #+#    #+#             */
/*   Updated: 2024/10/26 17:18:46 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" 

void	ft_error(char *s, t_cub *cub)
{
	printf ("Error\n cub3D: %s\n", s);
	if (cub && cub->d)
		freeall(cub->d);
	if (cub && cub->l)
		free (cub->l);
	exit (1);
}
void	check_number(t_cub *cub, int j, int i, int	l)
{
	char *d;

	while (cub->d[j][i] == 32)
			i++;
	l = i--;
	while (cub->d[j][++i])
	{
		if (cub->d[j][i] == ',')
		{
			d = ft_substr(cub->d[j], l, i - l);
			l = ft_atoi(d);
			free (d);
			if (!(l >= 0 && l <= 225))
				ft_error ("number C or F not valide", cub);
			l = i + 1;
		}
		else if (cub->d[j][i + 1] == '\0')
		{
			d = ft_substr(cub->d[j], l, i - l + 1);
			l = ft_atoi(d);
			free (d);
			if (!(l >= 0 && l <= 225))
				ft_error ("number C or F not valide", cub);
		}
	}
}

int	check_F_c(t_cub *cub, int i, int j, int k)
{
	int	d;

	d = i - 1;
	i++;
	while (cub->d[j][i] == 32)
			i++;
	if (cub->d[j][i] >= '0' && cub->d[j][i] <= '9')
	{
		while ((cub->d[j][i] >= '0' && cub->d[j][i] <= '9') || cub->d[j][i] == ',')
		{
			if (cub->d[j][i] == ',')
			{
				if (cub->d[j][i + 1] == ',')
					ft_error("map is not valide5", cub);
				k++;
			}
			i++;
		}
		if (cub->d[j][i - 1] == ',' || cub->d[j][i] || k != 2)
			ft_error("map is not valide6", cub);
		check_number(cub, j, 1, 0);
	}
	else
		ft_error("map not valide7", cub);
	return (d);
}

void	check_valid_con(t_cub *cub, int j, int i)
{
	if (cub->d[j][i] == 'N' && cub->d[j][i + 1] == 'O')
		cub->f[0]++;
	else if (cub->d[j][i] == 'S' && cub->d[j][i + 1] == 'O')
		cub->f[1]++;
	else if (cub->d[j][i] == 'W' && cub->d[j][i + 1] == 'E')
		cub->f[2]++;
	else if (cub->d[j][i] == 'E' && cub->d[j][i + 1] == 'A')
		cub->f[3]++;
	else if (cub->d[j][i] == 'F' && cub->d[j][i + 1] == ' ')
	{
		i = check_F_c(cub, i, j, 0);
		cub->f[4]++;
	}
	else if (cub->d[j][i] == 'C' && cub->d[j][i + 1] == ' ')
	{
		i = check_F_c(cub, i, j, 0);
		cub->f[5]++;
	}
	else
		ft_error("map not valide1", cub);
	i += 2;
	if (cub->d[j][i] == 32)
			i++;
	else
		ft_error("map not valide2", cub);
	if (!cub->d[j][i])
		ft_error("map not valide3", cub);
}

void	check_valid_file(t_cub *cub ,int i, int j)
{
	cub->f[0] = 0;
	cub->f[1] = 0;
	cub->f[2] = 0;
	cub->f[3] = 0;
	cub->f[4] = 0;
	cub->f[5] = 0;
	while (cub->d[++i])
		cub->d[i] = ft_strtrim(cub->d[i], " ");
	while (cub->d[++j])
	{
		i = 0;
		if (cub->d[j][i])
			check_valid_con(cub, j, i);
		if(cub->f[0] == 1 && cub->f[1] == 1 && cub->f[2] == 1
			&& cub->f[3] == 1 && cub->f[4] == 1 && cub->f[5] == 1)
			break;
		else if (cub->f[0] > 1 || cub->f[1] > 1 || cub->f[2] > 1
			|| cub->f[3] > 1 || cub->f[4] > 1 || cub->f[5] > 1)
			ft_error("map not valide8", cub);
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

void	parsing(char *s, t_cub *cub)
{
	int	i;
    char    *tmp;

	cub->l = NULL;
	i = ft_strlen(s, 0);
	if (i - 4 > 0 && !ft_strcmp(&s[i - 4], ".cub"))
	{
		i = open (s, O_RDONLY);
		if (i == -1)
			ft_error("file is not valide", NULL);
		tmp = get_next_line(i);
		while (tmp)
		{
			cub->l = ft_strjoin(cub->l, tmp);
			free (tmp);
			tmp = get_next_line(i);
		}
   		close(i);
		cub->d = ft_split(cub->l, '\n');
		check_valid_file(cub, -1, -1);
		tmp = ft_strdup(&cub->l[find_i(cub)]);
		char_check(tmp);
		player_nb(tmp);
		skep_nl(tmp);
		empty_sp(ft_split(tmp, '\n'), cub);
		free (tmp);
	}
	else
		ft_error("file name is not valide", NULL);
}
