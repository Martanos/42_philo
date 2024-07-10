/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:33:14 by malee             #+#    #+#             */
/*   Updated: 2024/07/10 16:33:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_eat(t_phil *phil)
{
	int	flag;

	pthread_mutex_lock(&phil->set_is_eating);
	flag = phil->is_eating;
	pthread_mutex_unlock(&phil->set_is_eating);
	return (flag);
}
ssize_t	ft_get_time_last_eaten(t_phil *phil)
{
	ssize_t	time;

	pthread_mutex_lock(&phil->set_time_last_eaten);
	time = phil->time_last_eaten;
	pthread_mutex_unlock(&phil->set_time_last_eaten);
	return (time);
}

void	ft_set_death(t_phil *phil, int flag)
{
	pthread_mutex_lock(&phil->rules->set_dead_phil);
	phil->rules->dead_phil = flag;
	pthread_mutex_unlock(&phil->rules->set_dead_phil);
}

int	ft_get_death(t_phil *phil)
{
	int flag;

	pthread_mutex_lock(&phil->rules->set_dead_phil);
	flag = phil->rules->dead_phil;
	pthread_mutex_unlock(&phil->rules->set_dead_phil);
	return (flag);
}
