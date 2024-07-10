/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:53:58 by malee             #+#    #+#             */
/*   Updated: 2024/07/10 17:54:06 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_phil_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (!ft_get_death(phil))
	{
		if (phil->rules->max_meals < 0
			|| phil->meals_eaten <= phil->rules->max_meals)
			ft_think_eat(phil);
		usleep(phil->rules->time_to_sleep * 1000 - 16000);
	}
	return (NULL);
}

void	ft_mise_en_place(t_phil *phils)
{
	pthread_t	reaper_thread;
	ssize_t		i;
	t_phil		*current;

	i = 0;
	current = phils;
	phils->rules->start_time = ft_get_time();
	while (++i <= phils->rules->num_of_phils)
	{
		ft_set_time_last_eaten(current);
		current->meals_eaten = 0;
		pthread_create(&(current->thread), NULL, ft_phil_routine, current);
		current = current->next_phil;
	}
	phils->rules->start_time = ft_get_time();
	pthread_create(&reaper_thread, NULL, ft_reaper, phils);
	pthread_join(reaper_thread, NULL);
	i = 0;
	current = phils;
	while (++i <= phils->rules->num_of_phils)
	{
		pthread_join(current->thread, NULL);
		current = current->next_phil;
	}
}

void	ft_think_eat(t_phil *phil)
{
	ft_print_status(phil, "is thinking");
	if (ft_get_meals_eaten(phil) == phil->rules->max_meals
		&& phil->rules->max_meals != -1)
	{
		ft_set_time_last_eaten(phil);
		return ;
	}
	if (ft_fork_order(phil))
		return ;
	ft_print_status(phil, "is eating");
	ft_set_eat(phil, 1);
	ft_set_time_last_eaten(phil);
	usleep(phil->rules->time_to_eat * 1000 - 16000);
	pthread_mutex_unlock(&phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
	if (phil->rules->max_meals > -1)
		ft_set_meals_eaten(phil);
	ft_set_eat(phil, 0);
	ft_print_status(phil, "is sleeping");
}

int	ft_fork_order(t_phil *phil)
{
	if (phil->rules->num_of_phils == 1)
	{
		pthread_mutex_lock(&phil->left_fork);
		ft_print_status(phil, "has taken a fork");
		pthread_mutex_unlock(&phil->left_fork);
		usleep(phil->rules->time_to_die * 1000);
		return (1);
	}
	else if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(&phil->left_fork);
		ft_print_status(phil, "has taken a fork");
		pthread_mutex_lock(phil->right_fork);
		ft_print_status(phil, "has taken a fork");
		return (0);
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
		ft_print_status(phil, "has taken a fork");
		pthread_mutex_lock(&phil->left_fork);
		ft_print_status(phil, "has taken a fork");
		return (0);
	}
}
