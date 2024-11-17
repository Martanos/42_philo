/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:47:50 by malee             #+#    #+#             */
/*   Updated: 2024/11/17 22:29:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static unsigned char	ft_check_death(t_monitor *monitor, int i)
{
	int64_t	current_time;

	current_time = ft_get_time();
	pthread_mutex_lock(&monitor->philos[i].meal_data_mutex);
	if (monitor->philos[i].last_meal_time
		+ monitor->time_to_die <= current_time)
	{
		pthread_mutex_unlock(&monitor->philos[i].meal_data_mutex);
		pthread_mutex_lock(&monitor->simulation_ended_mutex);
		monitor->simulation_ended = true;
		pthread_mutex_unlock(&monitor->simulation_ended_mutex);
		pthread_mutex_lock(&monitor->print_mutex);
		printf("%ld %d died\n", current_time - monitor->start_time,
			monitor->philos[i].id);
		pthread_mutex_unlock(&monitor->print_mutex);
		return (EXIT_SUCCESS);
	}
	else
		pthread_mutex_unlock(&monitor->philos[i].meal_data_mutex);
	return (EXIT_FAILURE);
}

// Acts as a delay as well
static unsigned char	ft_check_full(t_monitor *monitor)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&monitor->philos[i].full_mutex);
		if (monitor->philos[i].full == true)
			count++;
		pthread_mutex_unlock(&monitor->philos[i].full_mutex);
	}
	if (count == monitor->num_of_philos)
	{
		pthread_mutex_lock(&monitor->simulation_ended_mutex);
		monitor->simulation_ended = true;
		pthread_mutex_unlock(&monitor->simulation_ended_mutex);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

// NOTE: ONLY POSSIBLE PLACE DEATH MESSAGE CAN BE PRINTED
void	*ft_monitor_routine(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	while (1)
	{
		i = -1;
		while (++i < monitor->num_of_philos)
		{
			pthread_mutex_lock(&monitor->philos[i].full_mutex);
			if (monitor->philos[i].full == false)
			{
				pthread_mutex_unlock(&monitor->philos[i].full_mutex);
				if (ft_check_death(monitor, i) == EXIT_SUCCESS)
					return (NULL);
			}
			else
				pthread_mutex_unlock(&monitor->philos[i].full_mutex);
			if (ft_check_full(monitor) == EXIT_SUCCESS)
				return (NULL);
		}
	}
	return (NULL);
}
