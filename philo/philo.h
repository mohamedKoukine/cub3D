/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:53:47 by aelbouab          #+#    #+#             */
/*   Updated: 2024/09/16 17:59:48 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				ph_id;
	size_t			last_m;
	pthread_mutex_t	*l_forck;
	pthread_mutex_t	*r_forck;
	struct s_list	*info;
}			t_philo;

typedef struct s_list
{
	int				death;
	int				philos_nb;
	size_t			s_t;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nbr_dishes;
	size_t			meals;
	pthread_mutex_t	*forck;
	pthread_mutex_t	time;
	pthread_mutex_t	dishes;
	pthread_mutex_t	died;
	t_philo			*philos;
}			t_list;

size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		main(int ac, char **av);
char	**ft_split(char const *s, char c);
int		testdigit(int ac, char **av);
int		spacelloc(int ac, char **av, int i, int x);
void	freearray(char **cav, char *sav);
int		*parssing(int ac, char **av);
int		ft_isdigit(int i);
char	*rmspace1(char *av, char *sav, int i, int j);
char	*rmspace(char *av);
int		*testnsplite(char **av, int *a, int i, int x);
int		intlen(int *arr);
size_t	ft_cur_time(void);
int		death_note(t_philo *philo);
void	first_part(t_philo *philo);
void	second_part(t_philo *philo, size_t b, size_t a);
void	*thread_func(void *p);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *src);
void	ft_sleep(t_philo *philo, size_t a);
void	*fill_info1(int *arr, t_list *info, int i);
int		ft_mutex_init(t_list *info, int i);
void	death_func(t_list *info, int i);
void	fill_info(int *arr, t_list *info, int i);
int		destroy_forck(t_list *info, int i, int on);

#endif