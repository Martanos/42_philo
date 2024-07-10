/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:15:53 by malee             #+#    #+#             */
/*   Updated: 2024/07/10 17:44:45 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_reaper(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (1)
	{
		if (!ft_get_eat(phil) && ((ft_get_time()
					- ft_get_time_last_eaten(phil)) > phil->rules->time_to_die))
		{
			ft_print_status(phil, "died");
			ft_set_death(phil, 1);
			break ;
		}
		phil = phil->next_phil;
		if (phil->rules->max_meals != -1)
		{
			if (ft_fullness(phil))
				break ;
		}
		usleep(100);
	}
	return (NULL);
}

int	ft_fullness(t_phil *phil)
{
	t_phil	*current;
	ssize_t	i;

	i = 0;
	current = phil;
	while (i < phil->rules->num_of_phils)
	{
		if (current->meals_eaten != phil->rules->max_meals)
			return (0);
		current = current->next_phil;
		i++;
	}
	ft_set_death(phil, 1);
	return (1);
}
