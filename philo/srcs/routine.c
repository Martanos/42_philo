/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:20:31 by malee             #+#    #+#             */
/*   Updated: 2024/11/18 01:17:19 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static unsigned char	ft_eat(t_philo **philo, int64_t *meals_eaten)
{
	if (ft_take_forks(philo, *meals_eaten) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&(*philo)->meal_data_mutex);
	(*philo)->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&(*philo)->meal_data_mutex);
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
void	*ft_philosopher_routine(void *arg)
{
	t_philo	*philo;
	int64_t	meals_eaten;

	philo = (t_philo *)arg;
	meals_eaten = 0;
	pthread_mutex_lock(&philo->ready_mutex);
	philo->ready = true;
	pthread_mutex_unlock(&philo->ready_mutex);
	pthread_mutex_lock(&philo->monitor->all_ready_mutex);
	pthread_mutex_unlock(&philo->monitor->all_ready_mutex);
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
	pthread_mutex_lock(&philo->ready_mutex);
	philo->ready = true;
	pthread_mutex_unlock(&philo->ready_mutex);
	pthread_mutex_lock(&philo->monitor->all_ready_mutex);
	pthread_mutex_unlock(&philo->monitor->all_ready_mutex);
	ft_print_message(philo, "is thinking");
	ft_precise_sleep(philo->monitor->time_to_eat);
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
