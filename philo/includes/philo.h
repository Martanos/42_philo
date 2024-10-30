/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:03:11 by malee             #+#    #+#             */
/*   Updated: 2024/10/30 15:48:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//	alloc_err
# define ALLOC_ERR_THREAD "ERROR WHILE ALLOCATING THREADS IDs"
# define ALLOC_ERR_PHILO "ERROR WHILE ALLOCATING PHILOS"
# define ALLOC_ERR_FORK "ERROR WHILE ALLOCATING FORKS"
//	pthread_err
# define ERR_THREAD_CREATE "ERROR WHILE CREATING THREADS"
# define ERR_THREAD_JOIN "ERROR WHILE JOINING THREADS"
# define ERR_FORK_INIT "ERROR WHILE INIT FORKS"
//	time_err
# define ERR_TIME "UNABLE TO RETRIVE UTC"
//	philo_msg
# define TAKE_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread_id;
	ssize_t				philo_id;
	ssize_t				eat_cont;
	ssize_t				status;
	ssize_t				eating;
	ssize_t				time_to_die;
	pthread_mutex_t		lock;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_table				*table;

}						t_philo;

typedef struct s_table
{
	pthread_t			*thread_id;
	ssize_t				philo_num;
	ssize_t				meals_num;
	ssize_t				dead;
	ssize_t				finished;
	t_philo				*philos;
	ssize_t				death_time;
	ssize_t				eat_time;
	ssize_t				sleep_time;
	ssize_t				start_time;
	ssize_t				all_threads_ready;
	ssize_t				philo_count_ready;
	pthread_mutex_t		*forks;
	pthread_mutex_t		start_lock;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}						t_table;

// MAIN
int						main(int argc, char **argv);
int						ft_case_one(t_table *table);
int						ft_input_checker(char **argv);
// ROUTINES
void					*ft_monitor(void *data);
void					*ft_supervisor(void *philo_pointer);
void					*ft_routine(void *philo_pointer);
int						ft_thread_init(t_table *table);
int						ft_spawn_threads(t_table *table);
// ROUTINE UTILS
void					ft_take_forks(t_philo *philo);
void					ft_drop_forks(t_philo *philo);
void					ft_eat(t_philo *philo);
//	UTILS
ssize_t					ft_atoi_strict(char *str);
void					*ft_calloc(size_t nmemb, size_t size);
ssize_t					ft_get_time(void);
void					ft_precise_usleep(ssize_t time);
void					ft_print_status(char *str, t_philo *philo);
int						ft_strcmp(char *s1, char *s2);
// INIT UTILS
int						ft_init(t_table *table, char **argv, int argc);
int						ft_init_table(t_table *table);
int						ft_init_forks(t_table *table);
void					ft_init_philos(t_table *table);
int						ft_init_data(t_table *table, char **argv, int argc);
// ERROR HANDLING
int						ft_error(char *str, t_table *table);
void					ft_exit(t_table *table);
void					ft_clear_data(t_table *table);

#endif
