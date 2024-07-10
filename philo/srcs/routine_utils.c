/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:07:32 by malee             #+#    #+#             */
/*   Updated: 2024/07/10 16:32:44 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_eat(t_phil *phil, int flag)
{
	pthread_mutex_lock(&phil->set_is_eating);
	phil->is_eating = flag;
	pthread_mutex_unlock(&phil->set_is_eating);
}
void	ft_set_time_last_eaten(t_phil *phil)
{
	pthread_mutex_lock(&phil->set_time_last_eaten);
	phil->time_last_eaten = ft_get_time();
	pthread_mutex_unlock(&phil->set_time_last_eaten);
}

void	ft_print_status(t_phil *phil, char *status)
{
	if (!ft_get_death(phil))
	{
		pthread_mutex_lock(&phil->rules->is_printing);
		printf("%zd %zd %s\n", ft_get_time() - phil->rules->start_time,
			phil->id, status);
		pthread_mutex_unlock(&phil->rules->is_printing);
	}
}

void	ft_set_meals_eaten(t_phil *phils)
{
	pthread_mutex_lock(&phils->set_meals_eaten);
	phils->meals_eaten++;
	pthread_mutex_unlock(&phils->set_meals_eaten);
}
ssize_t	ft_get_meals_eaten(t_phil *phils)
{
	ssize_t	meals;

	pthread_mutex_lock(&phils->set_meals_eaten);
	meals = phils->meals_eaten;
	pthread_mutex_unlock(&phils->set_meals_eaten);
	return (meals);
}
