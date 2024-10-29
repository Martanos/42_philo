/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:22:34 by malee             #+#    #+#             */
/*   Updated: 2024/10/30 07:43:51 by malee            ###   ########.fr       */
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
		ft_precise_usleep(1);
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
		if (!philo->eating && ft_get_time() > philo->time_to_die)
			ft_print_status(DIED, philo);
		if (philo->eat_cont == philo->table->meals_num)
		{
			pthread_mutex_lock(&philo->table->lock);
			philo->table->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->table->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		ft_precise_usleep(1);
	}
	return ((void *)0);
}

void	*ft_routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = ft_get_time() + philo->table->death_time;
	if (pthread_create(&philo->thread_id, NULL, &ft_supervisor, (void *)philo))
		return ((void *)1);
	while (1)
	{
		pthread_mutex_lock(&philo->table->lock);
		if (philo->table->dead)
		{
			pthread_mutex_unlock(&philo->table->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->lock);
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
		i += 2;
		ft_precise_usleep(100);
	}
	i = 1;
	while (i < table->philo_num)
	{
		if (pthread_create(&table->thread_id[i], NULL, &ft_routine,
				&table->philos[i]))
			return (ft_error(ERR_THREAD_CREATE, table));
		i += 2;
		ft_precise_usleep(100);
	}
	return (0);
}

int	ft_thread_init(t_table *table)
{
	int			i;
	pthread_t	monitor_id;

	table->start_time = ft_get_time();
	if (table->meals_num > 0)
	{
		if (pthread_create(&monitor_id, NULL, &ft_monitor, &table->philos[0]))
			return (ft_error(ERR_THREAD_CREATE, table));
	}
	i = -1;
	while (++i < table->philo_num)
	{
		if (pthread_create(&table->thread_id[i], NULL, &ft_routine,
				&table->philos[i]))
			return (ft_error(ERR_THREAD_CREATE, table));
		ft_precise_usleep(1);
	}
	i = -1;
	while (++i < table->philo_num)
		if (pthread_join(table->thread_id[i], NULL))
			return (ft_error(ERR_THREAD_JOIN, table));
	if (table->meals_num > 0)
		pthread_join(monitor_id, NULL);
	return (0);
}
