/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:22:34 by malee             #+#    #+#             */
/*   Updated: 2024/10/30 16:13:32 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_monitor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->table->lock);
		if (philo->table->finished >= philo->table->philo_num
			|| philo->table->dead)
		{
			philo->table->dead = 1;
			pthread_mutex_unlock(&philo->table->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->lock);
	}
	return ((void *)0);
}

void	*ft_supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->eating == 0 && (ft_get_time() >= philo->time_to_die))
			ft_print_status(DIED, philo);
		if (philo->eat_cont == philo->table->meals_num)
		{
			pthread_mutex_lock(&philo->table->lock);
			philo->table->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->table->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		ft_precise_usleep(1000);
	}
	return ((void *)0);
}

void	*ft_routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(&philo->table->start_lock);
	philo->table->philo_count_ready++;
	if (philo->table->philo_count_ready == philo->table->philo_num)
		philo->table->all_threads_ready = 1;
	pthread_mutex_unlock(&philo->table->start_lock);
	while (!philo->table->all_threads_ready)
		usleep(100);
	if (philo->philo_id % 2 == 0)
		ft_precise_usleep(1);
	philo->time_to_die = philo->table->death_time + ft_get_time();
	if (pthread_create(&philo->thread_id, NULL, &ft_supervisor, (void *)philo))
		return ((void *)1);
	while (philo->table->dead == 0)
	{
		ft_eat(philo);
		ft_print_status(THINKING, philo);
	}
	if (pthread_join(philo->thread_id, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	ft_spawn_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_create(&table->thread_id[i], NULL, &ft_routine,
				&table->philos[i]))
			return (ft_error(ERR_THREAD_CREATE, table));
		i++;
	}
	return (0);
}

int	ft_thread_init(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	pthread_mutex_init(&table->start_lock, NULL);
	table->all_threads_ready = 0;
	table->philo_count_ready = 0;
	table->start_time = ft_get_time();
	if (table->meals_num > 0)
	{
		if (pthread_create(&monitor_thread, NULL, &ft_monitor,
				&table->philos[0]))
			return (ft_error(ERR_THREAD_CREATE, table));
	}
	if (ft_spawn_threads(table) != 0)
		return (1);
	i = -1;
	while (++i < table->philo_num)
		if (pthread_join(table->thread_id[i], NULL))
			return (ft_error(ERR_THREAD_JOIN, table));
	if (table->meals_num > 0)
		if (pthread_join(monitor_thread, NULL))
			return (ft_error(ERR_THREAD_JOIN, table));
	pthread_mutex_destroy(&table->start_lock);
	return (0);
}
