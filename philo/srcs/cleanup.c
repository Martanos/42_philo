/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:51:36 by malee             #+#    #+#             */
/*   Updated: 2024/11/17 22:29:35 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_free_philos(t_monitor **monitor)
{
	int	id;

	id = -1;
	while (++id < (*monitor)->num_of_philos)
	{
		pthread_mutex_destroy(&(*monitor)->philos[id].meal_data_mutex);
		pthread_mutex_destroy(&(*monitor)->philos[id].owned_fork->fork_mutex);
		free((*monitor)->philos[id].owned_fork);
	}
	free((*monitor)->philos);
}

// NOTE: This function is used to clean up the memory allocated for the monitor
unsigned char	ft_cleanup(t_monitor **monitor)
{
	if (&(*monitor)->simulation_ended_mutex)
		pthread_mutex_destroy(&(*monitor)->simulation_ended_mutex);
	if (&(*monitor)->print_mutex)
		pthread_mutex_destroy(&(*monitor)->print_mutex);
	ft_free_philos(monitor);
	return (EXIT_SUCCESS);
}
