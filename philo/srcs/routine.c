/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:20:31 by malee             #+#    #+#             */
/*   Updated: 2024/11/17 22:29:40 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static unsigned char	ft_eat(t_philo **philo, int64_t *meals_eaten)
{
	if (ft_take_forks(philo, *meals_eaten) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&(*philo)->monitor->simulation_ended_mutex);
	(*philo)->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&(*philo)->monitor->simulation_ended_mutex);
	ft_print_message(philo, "is eating");
	(*meals_eaten)++;
	ft_precise_sleep((*philo)->monitor->time_to_eat);
	pthread_mutex_unlock(&(*philo)->owned_fork->fork_mutex);
	pthread_mutex_unlock(&(*philo)->shared_fork->fork_mutex);
	return (EXIT_SUCCESS);
}

// NOTE: Things to consider:
// - Where to check for death
// - End conditions: simulation end or full;
void	*ft_odd_routine(void *arg)
{
	t_philo	*philo;
	int64_t	meals_eaten;

	philo = (t_philo *)arg;
	meals_eaten = 0;
	while (1)
	{
		if (ft_eat(&philo, &meals_eaten) == EXIT_FAILURE)
			return (NULL);
		if (ft_check_end_conditions(&philo, meals_eaten) == EXIT_SUCCESS)
			return (NULL);
		ft_print_message(&philo, "is sleeping");
		ft_precise_sleep(philo->monitor->time_to_sleep);
		if (ft_check_end_conditions(&philo, meals_eaten) == EXIT_SUCCESS)
			return (NULL);
		ft_print_message(&philo, "is thinking");
	}
}

void	*ft_even_routine(void *arg)
{
	t_philo	*philo;
	int64_t	meals_eaten;

	philo = (t_philo *)arg;
	meals_eaten = 0;
	while (1)
	{
		if (ft_check_end_conditions(&philo, meals_eaten) == EXIT_SUCCESS)
			return (NULL);
		ft_print_message(&philo, "is thinking");
		if (ft_eat(&philo, &meals_eaten) == EXIT_FAILURE)
			return (NULL);
		if (ft_check_end_conditions(&philo, meals_eaten) == EXIT_SUCCESS)
			return (NULL);
		ft_print_message(&philo, "is sleeping");
		ft_precise_sleep(philo->monitor->time_to_sleep);
	}
}
