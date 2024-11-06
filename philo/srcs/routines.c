/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:22:34 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 08:19:02 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		ft_think(philo);
		pthread_mutex_lock(philo->first_fork->mutex);
		ft_print_status(philo, "has taken a fork");
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(philo->first_fork->mutex);
		pthread_mutex_lock(philo->dead_mutex);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(philo->dead_mutex);
		ft_print_status(philo, "died");
		return (NULL);
	}
	if (philo->id % 2)
		usleep(100);
	while (!philo->data->someone_died && (!philo->meals_required
			|| philo->meals_eaten < philo->meals_required))
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void	ft_routine_loop(t_data **data)
{
	int	i;

	(*data)->start_time = ft_get_time();
	(*data)->someone_died = 0;
	i = -1;
	while (++i < (*data)->philo_count)
	{
		(*data)->philos[i].start_time = (*data)->start_time;
		(*data)->philos[i].last_meal_time = (*data)->start_time;
		if (pthread_create(&(*data)->philos[i].thread, NULL, ft_routine,
				&(*data)->philos[i]) != 0)
			printf("Error creating thread for philosopher %d\n", i + 1);
	}
	if (pthread_create(&(*data)->monitor_thread, NULL, ft_death_monitor,
			*data) != 0)
		printf("Error creating monitor thread\n");
	i = -1;
	while (++i < (*data)->philo_count)
		pthread_join((*data)->philos[i].thread, NULL);
	pthread_join((*data)->monitor_thread, NULL);
}
