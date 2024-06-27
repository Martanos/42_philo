/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:07:32 by malee             #+#    #+#             */
/*   Updated: 2024/06/28 00:15:27 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_rules *table, t_phil *phil)
{
	ft_print_status(table, phil, "is thinking");
}
void	ft_eat(t_rules *table, t_phil *phil)
{
	pthread_mutex_lock(&phil->left_fork);
	ft_print_status(table, phil, "has taken a fork");
	pthread_mutex_lock(phil->right_fork);
	ft_print_status(table, phil, "has taken a fork");
	ft_print_status(table, phil, "is eating");
	usleep(table->time_to_eat);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
}

void	ft_sleep(t_rules *table, t_phil *phil)
{
	ft_print_status(table, phil, "is sleeping");
	usleep(table->time_to_sleep);
}

void	ft_print_status(t_rules *table, t_phil *phil, char *status)
{
	pthread_mutex_lock(&table->is_printing);
	printf("%zu %zu %s\n", ft_get_time() - table->start_time, phil->id, status);
	pthread_mutex_unlock(&table->is_printing);
}
