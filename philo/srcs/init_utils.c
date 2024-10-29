/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:01:28 by malee             #+#    #+#             */
/*   Updated: 2024/10/29 21:54:37 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_init_mutexes(t_table **table)
{
	int	i;

	(*table)->forks = ft_calloc((*table)->num_philos, sizeof(pthread_mutex_t));
	if (!(*table)->forks)
		return (EXIT_FAILURE);
	i = 0;
	while (i < (*table)->num_philos)
	{
		if (pthread_mutex_init(&(*table)->forks[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_mutex_init(&(*table)->write_mutex, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(*table)->death_mutex, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_init_philos(t_table **table)
{
	int	i;

	(*table)->philosophers = ft_calloc((*table)->num_philos, sizeof(t_philo));
	if (!(*table)->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i < (*table)->num_philos)
	{
		(*table)->philosophers[i].id = i + 1;
		(*table)->philosophers[i].meals_eaten = 0;
		(*table)->philosophers[i].last_meal_time = ft_get_time();
		(*table)->philosophers[i].table = *table;
		(*table)->philosophers[i].left_fork = &(*table)->forks[i];
		(*table)->philosophers[i].right_fork = &(*table)->forks[(i + 1)
			% (*table)->num_philos];
		i++;
	}
	return (EXIT_SUCCESS);
}
