/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:03:11 by malee             #+#    #+#             */
/*   Updated: 2024/06/27 18:59:52 by malee            ###   ########.fr       */
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

typedef struct s_rules
{
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	ssize_t			max_meals;
	pthread_mutex_t	is_printing;
	struct s_phil	*phils;
}					t_rules;

typedef struct s_phil
{
	size_t			id;
	struct s_phil	*next_phil;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	size_t			last_eaten;
	size_t			meals_eaten;
	int				dead;
	pthread_t		thread;
}					t_phil;

// Utils
size_t				ft_atol(char *str);
int					ft_isdigit(char *str);
t_rules				*ft_init_table(char **args);
void				ft_error(void);

#endif
