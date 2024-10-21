/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:21:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/10/17 12:44:48 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
	t_all	all;
	t_cub	cub;
	t_player	player;

	all.cub = &cub;
	all.player = &player;
	if (ac == 2)
	{
		parsing(av[1], all.cub);
	}
	else
		printf ("Error\n cub3D: number of argement is not valide");
	ft_draw(&all);
}
