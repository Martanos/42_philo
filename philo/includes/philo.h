/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:03:11 by malee             #+#    #+#             */
/*   Updated: 2024/07/08 22:11:59 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# ifndef ERROR_CODE
#  define ERROR_CODE 0
# endif

typedef struct s_phil
{
	ssize_t			id;
	struct s_phil	*next_phil;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	set_time_last_eaten;
	ssize_t			time_last_eaten;
	ssize_t			meals_eaten;
	pthread_mutex_t	set_is_eating;
	int				is_eating;
	pthread_t		thread;
	struct s_rules	*rules;
}					t_phil;

typedef struct s_rules
{
	ssize_t			num_of_phils;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			max_meals;
	ssize_t			start_time;
	pthread_mutex_t	set_dead_phil;
	int				dead_phil;
	pthread_mutex_t	is_printing;
}					t_rules;

// Utils
ssize_t				ft_atol(char *str);
int					ft_isdigit(char *str);
void				ft_error(void);
ssize_t				ft_get_time(void);
void				*ft_calloc(ssize_t nmemb, ssize_t size);

// Init_Utils
t_phil				*ft_init_table(char **args);
t_phil				*ft_init_phils(t_rules *rules, ssize_t start);
t_rules				*ft_init_rules(char **args);

// routines

void				*ft_reaper(void *arg);

// rountine utils
void				ft_think_eat(t_phil *phil);
void				ft_sleep(t_phil *phil);
void				ft_set_eat(t_phil *phil, int flag);
void				ft_set_time_last_eaten(t_phil *phil);
void				ft_print_status(t_phil *phil, char *status);

#endif
