/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:49:59 by malee             #+#    #+#             */
/*   Updated: 2024/10/29 20:45:05 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_start_simulation(t_table **table)
{
	int	i;

	i = 0;
	while (i < (*table)->num_philos)
	{
		(*table)->philosophers[i].last_meal_time = ft_get_time();
		if (pthread_create(&(*table)->philosophers[i].thread, NULL,
				ft_philosopher_routine, &(*table)->philosophers[i]))
			return (EXIT_FAILURE);
		i++;
	}
	(*table)->start_time = ft_get_time();
	i = 0;
	while (i < (*table)->num_philos)
	{
		pthread_detach((*table)->philosophers[i].thread);
		i++;
	}
	ft_reaper_routine(table);
	return (EXIT_SUCCESS);
}
