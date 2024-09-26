/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:54:43 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/09/26 10:44:02 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error(char *s)
{
	printf ("Error\n cub3D: %s\n", s);
	exit (1);
}


void	check_F_c(char *l,int i)
{
	int	j;
	
	j = 0;
	i++;
	while (l[i] == 32)
			i++;
	if (l[i] >= '0' && l[i] <= '9')
	{
		while ((l[i] >= '0' && l[i] <= '9') || l[i] == ',')
		{
			if (l[i] == ',')
			{
				if (l[i + 1] == ',')
					ft_error("map is not valide5");
				j++;
			}
			i++;
		}
		if (l[i - 1] == ',' || (l[i] != ' ' && l[i] != '\n') || j != 2)
			ft_error("map is not valide6");
	}
	else
	{
		free (l);
		ft_error("map not valide7");
	}
}
int	check_valid_file(char *l, int n, int s, int w)
{
	int		i;
	int		e;
	int		f;
	int		c;
	
	i = 0;
	f = 0;
	c = 0;
	e = 0;
   
	while (l[i])
	{
		while (l[i] == 10 || l[i] == 32)
			i++;
		if ((i == 0 || l[i - 1] == '\n') && (l[i] == 'N' && l[i + 1] == 'O'))
			n++;
		else if ((i == 0 || l[i - 1] == '\n') && (l[i] == 'S' && l[i + 1] == 'O'))
			s++;
		else if ((i == 0 || l[i - 1] == '\n') && (l[i] == 'W' && l[i + 1] == 'E'))
			w++;
		else if ((i == 0 || l[i - 1] == '\n') && (l[i] == 'E' && l[i + 1] == 'A'))
			e++;
		else if ((i == 0 || l[i - 1] == '\n') && (l[i] == 'F'))
		{
			check_F_c(l, i);
			i--;
			f++;
		}
		else if ((i == 0 || l[i - 1] == '\n') && (l[i] == 'C'))
		{
			check_F_c(l, i);
			i--;
			c++;
		}
		else
		{
			free (l);
			ft_error("map not valide1");
		}
		i += 2;
		if (l[i] == 32)
		{
			while (l[i] == 32)
				i++;
		}
		else
		{
			free (l);
			ft_error("map not valide2");
		}
		if (l[i] != 10 && l[i] != 32 && l[i])
		{
			while (l[i] != 10 && l[i] != 32 && l[i])
				i++;
		}
		else
		{
			free (l);
			ft_error("map not valide3");
		}
		if(n == 1 && s == 1 && w == 1 && e == 1 && f == 1 && c == 1)
			break;
	}
	return (i);
}
void	parsing(char *s)
{
	int	i;
	char    *l;
    char    *tmp;

	l = NULL;
	i = ft_strlen(s, 0);
	if (i - 4 > 0 && !ft_strcmp(&s[i - 4], ".cub"))
	{
		i = open (s, O_RDONLY);
		if (i == -1)
			ft_error("file is not valide");
		 tmp = get_next_line(i);
		while (tmp)
		{
			l = ft_strjoin(l, tmp);
			tmp = get_next_line(i);
		}
   		close(i);
		tmp = ft_strdup(&l[check_valid_file(l, 0, 0, 0)]);
		char_check(tmp);
		player_nb(tmp);
		skep_nl(tmp);
		empty_sp(ft_split(tmp, '\n'));
	}
	else
		ft_error("file name is not valide");
}

int main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 2)
	{
		parsing(av[1]);
	}
	else
		printf ("Error\n cub3D: number of argement is not valide");
}