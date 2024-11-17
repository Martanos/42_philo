/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:02:41 by malee             #+#    #+#             */
/*   Updated: 2024/11/17 22:29:43 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*ft_the_loneliness_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%ld %d has taken a fork\n", ft_get_time()
		- philo->monitor->start_time, philo->id);
	ft_precise_sleep(philo->monitor->time_to_die);
	printf("%ld %d died\n", ft_get_time() - philo->monitor->start_time,
		philo->id);
	return (NULL);
}

static void	ft_loneliness(t_philo *philo)
{
	philo->last_meal_time = ft_get_time();
	pthread_create(&philo->thread, NULL, ft_the_loneliness_routine, philo);
	pthread_join(philo->thread, NULL);
}

// ENSURES ALL PHILOSOPHERS START AT THE SAME TIME
static void	ft_set_time(t_monitor **monitor)
{
	int64_t	current_time;
	int		i;

	current_time = ft_get_time();
	(*monitor)->start_time = current_time;
	i = -1;
	while (++i < (*monitor)->num_of_philos)
		(*monitor)->philos[i].last_meal_time = current_time;
}

void	ft_simulation(t_monitor **monitor)
{
	pthread_t	monitor_thread;
	int			i;

	ft_set_time(monitor);
	if ((*monitor)->num_of_philos == 1)
		return (ft_loneliness(&(*monitor)->philos[0]));
	i = -1;
	while (++i < (*monitor)->num_of_philos)
	{
		if ((i + 1) % 2 == 0)
			pthread_create(&(*monitor)->philos[i].thread, NULL, ft_even_routine,
				&(*monitor)->philos[i]);
		else
			pthread_create(&(*monitor)->philos[i].thread, NULL, ft_odd_routine,
				&(*monitor)->philos[i]);
	}
	pthread_create(&monitor_thread, NULL, ft_monitor_routine, *monitor);
	i = -1;
	while (++i < (*monitor)->num_of_philos)
		pthread_join((*monitor)->philos[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
}
