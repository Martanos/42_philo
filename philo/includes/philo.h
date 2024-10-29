/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:03:11 by malee             #+#    #+#             */
/*   Updated: 2024/10/29 22:00:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define INT_SIZE_MAX 2147483647

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	long long			id;
	long long			meals_eaten;
	long long			last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long long			num_philos;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			meals_required;
	long long			someone_died;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		death_mutex;
	t_philo				*philosophers;
}						t_table;

/* SIMULATION */
int						ft_start_simulation(t_table **table);

/* ROUTINES */
void					*ft_philosopher_routine(void *arg);
void					ft_reaper_routine(t_table **table);

/* LIBFT UTILS */
void					*ft_calloc(ssize_t nmemb, ssize_t size);
long long				ft_atol(char *str);
int						ft_isdigit(char *str);

/* UTILITIES */
int						ft_init_mutexes(t_table **table);
int						ft_init_philos(t_table **table);
long long				ft_get_time(void);
int						ft_check_death(t_philo **philo);
void					ft_print_status(t_philo **philo, char *status);

#endif
