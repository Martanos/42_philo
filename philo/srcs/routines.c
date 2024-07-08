/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:17:16 by malee             #+#    #+#             */
/*   Updated: 2024/07/08 22:47:11 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_phil_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (phil->rules->dead_phil == 0)
	{
		if (phil->rules->max_meals < 0
			|| phil->meals_eaten <= phil->rules->max_meals)
			ft_think_eat(phil);
		if (phil->rules->dead_phil)
			break ;
		ft_sleep(phil);
		if (phil->rules->dead_phil)
			break ;
	}
}

void	ft_mise_en_place(t_phil *phils)
{
	t_phil	*current;

	phils->rules->start_time = ft_get_time();
	current = phils;
	while (current->id != phils->rules->num_of_phils)
	{
		pthread_create(&(current->thread), NULL, ft_phil_routine, current);
		current = phils->next_phil;
	}
}
