/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:03:11 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 08:06:36 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef struct s_data	t_data;

typedef struct s_data
{
	t_philo				*philos;
	t_fork				*forks;
	pthread_t			monitor_thread;
	int					all_meals_complete;
	int					philo_count;
	int					someone_died;
	pthread_mutex_t		*death_mutex;
	int64_t				start_time;
	pthread_mutex_t		*print_mutex;
}						t_data;

typedef struct s_fork
{
	pthread_mutex_t		*mutex;
	int					id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	t_data				*data;
	pthread_t			thread;
	int64_t				time_to_die;
	int64_t				time_to_eat;
	int64_t				time_to_sleep;
	int					meals_required;
	int					meals_eaten;
	pthread_mutex_t		*meals_mutex;
	int64_t				last_meal_time;
	pthread_mutex_t		*meal_time_mutex;
	int					is_dead;
	pthread_mutex_t		*dead_mutex;
	t_fork				*first_fork;
	t_fork				*second_fork;
	int64_t				start_time;
}						t_philo;

// MAIN
int						main(int argc, char **argv);
// INIT
int						ft_init(t_data **data, char **argv, int argc);
// THREADS
void					*ft_routine(void *arg);
void					*ft_death_monitor(void *arg);
// ROUTINES
void					ft_routine_loop(t_data **data);
void					*ft_death_monitor(void *arg);
// UTILS
void					*ft_calloc(int64_t nmemb, int64_t size);
void					ft_print_status(t_philo *philo, char *status);
void					ft_sleep(t_philo *philo);
void					ft_eat(t_philo *philo);
void					ft_think(t_philo *philo);
int64_t					ft_get_time(void);
int64_t					ft_atoi_strict(char *str);
// CLEAR
void					ft_clear_data(t_data **data);

#endif
