/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:15:53 by malee             #+#    #+#             */
/*   Updated: 2024/07/08 22:22:39 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_reaper(void *arg)
{
	t_phil	*phil;
	ssize_t	current_time;
	ssize_t	time_last_eaten;
	int		is_eating;

	phil = (t_phil *)arg;
	while (phil->rules->dead_phil == 0)
	{
		is_eating = ft_get_eat(&phil);
		current_time = ft_get_time();
		time_last_eaten = ft_get_time_last_eaten(&phil);
		if (!is_eating && ((current_time
					- time_last_eaten) > phil->rules->time_to_die))
		{
			ft_print_status(phil, "has died");
			ft_set_death(&phil, 1);
		}
		phil = phil->next_phil;
	}
}

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
