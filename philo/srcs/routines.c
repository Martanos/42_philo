/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:22:34 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 09:39:46 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		ft_print_status(philo, "has taken a fork");
		ft_precise_sleep(philo->time_to_die);
		pthread_mutex_lock(&philo->dead_mutex);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->dead_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died\n", ft_get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (NULL);
	}
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died || philo->data->all_meals_complete)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->meals_mutex);
		if (philo->meals_required > -1
			&& philo->meals_eaten >= philo->meals_required)
		{
			pthread_mutex_unlock(&philo->meals_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->meals_mutex);
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
	}
	i = -1;
	while (++i < (*data)->philo_count)
	{
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
