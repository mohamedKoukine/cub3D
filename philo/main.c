/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:16:43 by aelbouab          #+#    #+#             */
/*   Updated: 2024/11/02 10:09:49 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft(void)
{
	system("leaks philo");
}

int	destroy_forck(t_list *info, int i, int on)
{
	if (on)
		perror("pthread_mutex_create");
	pthread_mutex_destroy(&info->time);
	pthread_mutex_destroy(&info->died);
	pthread_mutex_destroy(&info->dishes);
	while (i >= 0)
	{
		pthread_mutex_destroy(&info->forck[i]);
		i--;
	}
	return (0);
}

void	ft_sleep(t_philo *philo, size_t a)
{
	a = ft_cur_time();
	while ((ft_cur_time() - a) < philo->info->time_to_eat)
	{
		pthread_mutex_lock(&philo->info->died);
		if (!philo->info->death)
		{
			pthread_mutex_unlock(&philo->info->died);
			break ;
		}
		pthread_mutex_unlock(&philo->info->died);
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	t_list	info;
	int		*arr;

	arr = parssing(ac, av);
	if (!arr)
		return (0);
	fill_info(arr, &info, 0);
	free (info.philos);
	free (info.forck);
	destroy_forck(&info, info.philos_nb - 1, 0);
}
