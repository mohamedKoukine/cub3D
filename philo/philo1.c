/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:02:25 by aelbouab          #+#    #+#             */
/*   Updated: 2024/09/24 11:20:42 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_cur_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	death_note(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->time);
	if (philo->info->death == 0)
	{
		pthread_mutex_unlock(&philo->info->time);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->time);
	return (0);
}

void	first_part(t_philo *philo)
{
	pthread_mutex_lock(philo->l_forck);
	pthread_mutex_lock(&philo->info->died);
	if (philo->info->death)
		printf ("%zu %d has taken a fork\n",
			ft_cur_time() - philo->info->s_t, philo->ph_id);
	pthread_mutex_unlock(&philo->info->died);
	pthread_mutex_lock(philo->r_forck);
	pthread_mutex_lock(&philo->info->died);
	if (philo->info->death)
	{
		printf ("%zu %d has taken a fork\n",
			ft_cur_time() - philo->info->s_t, philo->ph_id);
		printf ("%zu %d is eating\n",
			ft_cur_time() - philo->info->s_t, philo->ph_id);
		pthread_mutex_lock(&philo->info->dishes);
		philo->info->meals++;
		pthread_mutex_unlock(&philo->info->dishes);
	}
	pthread_mutex_unlock(&philo->info->died);
	pthread_mutex_lock(&philo->info->time);
	philo->last_m = ft_cur_time();
	pthread_mutex_unlock(&philo->info->time);
}

void	second_part(t_philo *philo, size_t b, size_t a)
{
	ft_sleep(philo, a);
	pthread_mutex_unlock(philo->l_forck);
	pthread_mutex_unlock(philo->r_forck);
	pthread_mutex_lock(&philo->info->died);
	if (philo->info->death)
		printf ("%zu %d is sleeping\n",
			ft_cur_time() - philo->info->s_t, philo->ph_id);
	pthread_mutex_unlock(&philo->info->died);
	b = ft_cur_time();
	while ((ft_cur_time() - b) < philo->info->time_to_sleep)
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
	pthread_mutex_lock(&philo->info->died);
	if (philo->info->death)
		printf ("%zu %d is thinking\n",
			ft_cur_time() - philo->info->s_t, philo->ph_id);
	pthread_mutex_unlock(&philo->info->died);
}

void	*thread_func(void *p)
{
	t_philo	*philo;

	philo = p;
	if (philo->ph_id % 2 == 0)
		usleep (500);
	while (1)
	{
		pthread_mutex_lock(&philo->info->dishes);
		if (philo->info->nbr_dishes)
		{
			if ((philo->info->meals / (size_t)philo->info->philos_nb)
				>= philo->info->nbr_dishes)
			{
				pthread_mutex_unlock(&philo->info->dishes);
				break ;
			}
		}
		pthread_mutex_unlock(&philo->info->dishes);
		if (death_note(philo))
			break ;
		first_part(philo);
		second_part(philo, 0, 0);
	}
	return (NULL);
}
