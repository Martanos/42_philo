/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:19:17 by malee             #+#    #+#             */
/*   Updated: 2024/11/17 22:31:18 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static unsigned char	ft_take_own_fork(t_philo **philo, int64_t meals_eaten)
{
	while (1)
	{
		pthread_mutex_lock(&(*philo)->owned_fork->fork_mutex);
		if (ft_check_end_conditions(philo, meals_eaten) == EXIT_SUCCESS)
		{
			pthread_mutex_unlock(&(*philo)->owned_fork->fork_mutex);
			return (EXIT_FAILURE);
		}
		else if ((*philo)->owned_fork->owner_last_used_time > (*philo)->owned_fork->partner_last_used_time)
			pthread_mutex_unlock(&(*philo)->owned_fork->fork_mutex);
		else
		{
			ft_print_message(philo, "has taken a fork");
			break ;
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

static unsigned char	ft_take_shared_fork(t_philo **philo,
		int64_t meals_eaten)
{
	while (1)
	{
		pthread_mutex_lock(&(*philo)->shared_fork->fork_mutex);
		if (ft_check_end_conditions(philo, meals_eaten) == EXIT_SUCCESS)
		{
			pthread_mutex_unlock(&(*philo)->shared_fork->fork_mutex);
			return (EXIT_FAILURE);
		}
		else if ((*philo)->shared_fork->partner_last_used_time > (*philo)->shared_fork->owner_last_used_time)
			pthread_mutex_unlock(&(*philo)->shared_fork->fork_mutex);
		else
		{
			ft_print_message(philo, "has taken a fork");
			break ;
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

unsigned char	ft_take_forks(t_philo **philo, int64_t meals_eaten)
{
	int64_t	current_time;

	if (ft_take_own_fork(philo, meals_eaten) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_take_shared_fork(philo, meals_eaten) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	current_time = ft_get_time();
	(*philo)->owned_fork->owner_last_used_time = current_time;
	(*philo)->shared_fork->partner_last_used_time = current_time;
	return (EXIT_SUCCESS);
}

unsigned char	ft_check_end_conditions(t_philo **philo, int64_t meals_eaten)
{
	pthread_mutex_lock(&(*philo)->monitor->simulation_ended_mutex);
	if ((*philo)->monitor->simulation_ended == true)
	{
		pthread_mutex_unlock(&(*philo)->monitor->simulation_ended_mutex);
		return (EXIT_SUCCESS);
	}
	else
		pthread_mutex_unlock(&(*philo)->monitor->simulation_ended_mutex);
	if ((*philo)->monitor->max_num_of_meals != -1
		&& meals_eaten == (*philo)->monitor->max_num_of_meals)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
