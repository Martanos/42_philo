/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:27:55 by malee             #+#    #+#             */
/*   Updated: 2024/11/18 00:27:31 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_philo		t_philo;
typedef struct s_monitor	t_monitor;
typedef struct s_fork		t_fork;

typedef struct s_fork
{
	pthread_mutex_t			fork_mutex;
	int						owner_id;
	int64_t					owner_last_used_time;
	int64_t					partner_last_used_time;
}							t_fork;

typedef struct s_philo
{
	t_monitor				*monitor;
	int						id;
	pthread_t				thread;
	t_fork					*owned_fork;
	t_fork					*shared_fork;
	pthread_mutex_t			full_mutex;
	bool					full;
	pthread_mutex_t			meal_data_mutex;
	int64_t					last_meal_time;
	pthread_mutex_t			ready_mutex;
	bool					ready;
}							t_philo;

typedef struct s_monitor
{
	int						num_of_philos;
	pthread_mutex_t			simulation_ended_mutex;
	bool					simulation_ended;
	pthread_mutex_t			print_mutex;
	t_philo					*philos;
	int64_t					start_time;
	int64_t					time_to_die;
	int64_t					time_to_eat;
	int64_t					time_to_sleep;
	int64_t					max_num_of_meals;
}							t_monitor;

// MAIN
int							main(int argc, char **argv);

// Checker
unsigned char				ft_checker(int argc, char **argv);

// Mise en place
unsigned char				ft_mise_en_place(int argc, char **argv,
								t_monitor **monitor);

// Simulation
void						ft_simulation(t_monitor **monitor);

// Routines
void						*ft_odd_routine(void *arg);
void						*ft_even_routine(void *arg);

// Monitor
void						*ft_monitor_routine(void *arg);

// Routine utils
unsigned char				ft_take_forks(t_philo **philo, int64_t meals_eaten);
unsigned char				ft_check_end_conditions(t_philo **philo,
								int64_t meals_eaten);

// Cleanup
unsigned char				ft_cleanup(t_monitor **monitor);

// Utils
int64_t						ft_atoi_strict(char *str);
void						*ft_calloc(int64_t nmemb, int64_t size);
int64_t						ft_get_time(void);
void						ft_precise_sleep(int64_t time_in_ms);
void						ft_print_message(t_philo **philo, char *message);

#endif
