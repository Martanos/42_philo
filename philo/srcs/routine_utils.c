/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:20:24 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 09:33:49 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_print_status(t_philo *philo, char *status)
{
	int64_t	current_time;

	pthread_mutex_lock(&(*philo).data->print_mutex);
	pthread_mutex_lock(&(*philo).dead_mutex);
	pthread_mutex_lock(&(*philo).meals_mutex);
	if (!philo->data->someone_died && (philo->meals_required == -1
			|| philo->meals_eaten < philo->meals_required))
	{
		current_time = ft_get_time() - philo->start_time;
		printf("%ld %d %s\n", current_time, philo->id, status);
	}
	pthread_mutex_unlock(&(*philo).meals_mutex);
	pthread_mutex_unlock(&(*philo).dead_mutex);
	pthread_mutex_unlock(&(*philo).data->print_mutex);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mutex);
	ft_print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->mutex);
	ft_print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	ft_print_status(philo, "is eating");
	ft_precise_sleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
	pthread_mutex_unlock(&philo->second_fork->mutex);
	pthread_mutex_unlock(&philo->first_fork->mutex);
}

void	ft_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking");
}
