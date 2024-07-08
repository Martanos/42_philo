/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:07:32 by malee             #+#    #+#             */
/*   Updated: 2024/07/08 22:27:55 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think_eat(t_phil *phil)
{
	ft_print_status(phil, "is thinking");
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(&phil->right_fork);
		ft_print_status(phil, "has taken its right fork");
		pthread_mutex_lock(&phil->left_fork);
		ft_print_status(phil, "has taken its left fork");
	}
	else
	{
		pthread_mutex_lock(&phil->left_fork);
		ft_print_status(phil, "has taken its left fork");
		pthread_mutex_lock(&phil->right_fork);
		ft_print_status(phil, "has taken its right fork");
	}
	ft_print_status(phil, "is eating");
	ft_set_eat(&phil, 1);
	ft_set_time_last_eaten(&phil);
	usleep(phil->rules->time_to_eat * 1000);
	if (phil->rules->max_meals > -1)
		phil->meals_eaten++;
	ft_set_time_last_eaten(&phil);
	ft_set_eat(&phil, 0);
	pthread_mutex_unlock(&phil->left_fork);
	pthread_mutex_unlock(&phil->right_fork);
}

void	ft_sleep(t_phil *phil)
{
	ft_print_status(phil, "is sleeping");
	usleep(phil->rules->time_to_eat * 1000);
}
void	ft_set_eat(t_phil *phil, int flag)
{
	pthread_mutex_lock(&phil->set_is_eating);
	phil->is_eating = flag;
	pthread_mutex_unlock(&phil->set_is_eating);
}
void	ft_set_time_last_eaten(t_phil *phil)
{
	pthread_mutex_lock(&phil->set_time_last_eaten);
	phil->time_last_eaten = ft_get_time;
	pthread_mutex_lock(&phil->set_time_last_eaten);
}

void	ft_print_status(t_phil *phil, char *status)
{
	pthread_mutex_lock(&phil->rules->is_printing);
	printf("%zd %zd %s\n", ft_get_time() - phil->rules->start_time, phil->id,
		status);
	pthread_mutex_unlock(&phil->rules->is_printing);
}
