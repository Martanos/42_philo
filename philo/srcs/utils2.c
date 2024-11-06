/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:14:33 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 07:59:08 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_clear_data(t_data **data)
{
	int	i;

	i = -1;
	while (++i < (*data)->philo_count)
	{
		pthread_mutex_destroy((*data)->philos[i].dead_mutex);
		pthread_mutex_destroy((*data)->philos[i].meal_time_mutex);
		pthread_mutex_destroy((*data)->philos[i].meals_mutex);
		free((*data)->philos[i].meals_mutex);
		free((*data)->philos[i].meal_time_mutex);
		free((*data)->philos[i].dead_mutex);
	}
	i = -1;
	while (++i < (*data)->philo_count)
	{
		pthread_mutex_destroy((*data)->forks[i].mutex);
		free((*data)->forks[i].mutex);
	}
	pthread_mutex_destroy((*data)->death_mutex);
	free((*data)->death_mutex);
	pthread_mutex_destroy((*data)->print_mutex);
	free((*data)->print_mutex);
	free(*data);
}
