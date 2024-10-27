/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:21:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/10/26 13:17:47 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_all		all;
	t_cub		cub;
	t_player	player;

	all.cub = &cub;
	all.player = &player;
	if (ac == 2)
	{
		parsing(av[1], all.cub);
		ft_draw(&all);
	}
	else
		printf ("Error\n cub3D: number of argement is not valide");
}
