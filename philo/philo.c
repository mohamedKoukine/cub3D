/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:55:56 by aelbouab          #+#    #+#             */
/*   Updated: 2024/11/02 10:30:30 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*fill_info1(int *arr, t_list *info, int i)
{
	info->s_t = ft_cur_time();
	info->death = 1;
	info->philos_nb = arr[0];
	info->time_to_die = arr[1];
	info->time_to_eat = arr[2];
	info->time_to_sleep = arr[3];
	if (intlen(arr) == 5)
		info->nbr_dishes = arr[4];
	else
		info->nbr_dishes = 0;
	info->meals = 0;
	free (arr);
	info->philos = malloc (sizeof(t_philo) * (info->philos_nb));
	if (!info->philos)
		return (NULL);
	info->forck = malloc (sizeof(pthread_mutex_t) * (info->philos_nb));
	if (!info->philos)
		return (NULL);
	while (i <= info->philos_nb)
	{
		info->philos[i - 1].ph_id = i;
		info->philos[i - 1].info = info;
		i++;
	}
	return (info->philos);
}

int	ft_mutex_init(t_list *info, int i)
{
	if (pthread_mutex_init(&info->time, NULL) != 0)
		return (perror("pthread_mutex_create"), 0);
	if (pthread_mutex_init(&info->died, NULL) != 0)
	{
		pthread_mutex_destroy(&info->time);
		return (perror("pthread_mutex_create"), 0);
	}
	if (pthread_mutex_init(&info->dishes, NULL) != 0)
	{
		pthread_mutex_destroy(&info->time);
		pthread_mutex_destroy(&info->died);
		return (perror("pthread_mutex_create"), 0);
	}
	while (++i < info->philos_nb)
	{
		if (pthread_mutex_init(&info->forck[i], NULL) != 0)
		{
			destroy_forck(info, i - 1, 1);
			return (0);
		}
	}
	i = 0;
	while (i < info->philos_nb)
		info->philos[i++].last_m = ft_cur_time();
	return (1);
}

int	nbr_meals(t_list *info)
{
	pthread_mutex_lock(&info->dishes);
	if (info->nbr_dishes)
	{
		if ((info->meals / (size_t)info->philos_nb) >= info->nbr_dishes)
		{
			pthread_mutex_unlock(&info->dishes);
			return (0);
		}
	}
	pthread_mutex_unlock(&info->dishes);
	return (1);
}

void	death_func(t_list *info, int i)
{
	while (1)
	{
		pthread_mutex_lock(&info->time);
		if ((ft_cur_time() - info->philos[i].last_m) > info->time_to_die)
		{
			pthread_mutex_lock(&info->died);
			info->death = 0;
			pthread_mutex_unlock(&info->died);
			if (!nbr_meals(info))
			{
				pthread_mutex_unlock(&info->time);
				break ;
			}
			printf ("%zu %d died\n",
				ft_cur_time() - info->s_t, info->philos[i].ph_id);
			pthread_mutex_unlock(&info->time);
			if (info->philos_nb == 1)
				pthread_mutex_unlock(info->philos->l_forck);
			break ;
		}
		pthread_mutex_unlock(&info->time);
		i++;
		if (i == info->philos_nb)
			i = 0;
	}
}

void	fill_info(int *arr, t_list *info, int i)
{
	if (!fill_info1(arr, info, 1))
		return ;
	if (!ft_mutex_init(info, -1))
		return ;
	while (i < info->philos_nb)
	{
		info->philos[i].l_forck = &info->forck[i];
		if (i + 1 != info->philos_nb)
			info->philos[i].r_forck = &info->forck[i + 1];
		else
			info->philos[i].r_forck = &info->forck[0];
		if (pthread_create(&(info->philos[i].thread), NULL,
				thread_func, &info->philos[i]) != 0)
			return (perror("pthread_create"));
		i++;
	}
	death_func(info, 0);
	i = 0;
	while (i < info->philos_nb)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
}
