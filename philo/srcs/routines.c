/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:17:16 by malee             #+#    #+#             */
/*   Updated: 2024/06/28 00:24:46 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_phil_routine(void *arg)
{
	t_rules	*table;

	table = (t_rules *)arg;
	while (!table->simulation_stop)
	{
		ft_think(table, table->phils);
		if (table->simulation_stop)
			break ;
		ft_eat(table, table->phils);
		if (table->simulation_stop)
			break ;
		ft_sleep(table, table->phils);
	}
	return (NULL);
}

void	ft_simulation(t_rules *table)
{
	t_phil		*phil;
	size_t		i;
	pthread_t	monitor_thread;

	i = 1;
	phil = table->phils;
	table->start_time = ft_get_time();
	while (i <= table->num_of_phils)
	{
		phil->last_eaten = table->start_time;
		pthread_create(&phil->thread, NULL, ft_phil_routine, table);
		table->phils = phil->next_phil;
		i++;
	}
	table->phils = phil;
	pthread_create(&monitor_thread, NULL, ft_monitor, table);
	i = 1;
	while (i <= table->num_of_phils)
	{
		pthread_join(phil->thread, NULL);
		phil = phil->next_phil;
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int	ft_check_death(t_phil *philo, t_rules *rules)
{
	size_t	current_time;

	current_time = ft_get_time();
	if ((current_time - philo->last_eaten) > rules->time_to_die)
	{
		pthread_mutex_lock(&rules->death_check);
		if (!rules->simulation_stop)
		{
			rules->simulation_stop = 1;
			printf("%zu %zu died\n", current_time - rules->start_time,
				philo->id);
		}
		pthread_mutex_unlock(&rules->death_check);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_rules	*rules;
	t_phil	*philo;

	rules = (t_rules *)arg;
	philo = rules->phils;
	while (!rules->simulation_stop)
	{
		if (ft_check_death(philo, rules))
			break ;
		philo = philo->next_phil;
		usleep(1000);
	}
	return (NULL);
}
