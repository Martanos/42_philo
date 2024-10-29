/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:20:24 by malee             #+#    #+#             */
/*   Updated: 2024/10/30 07:47:28 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(TAKE_FORK, philo);
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(TAKE_FORK, philo);
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print_status(SLEEPING, philo);
	ft_precise_usleep(philo->table->sleep_time);
}

void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = ft_get_time() + philo->table->death_time;
	ft_print_status(EATING, philo);
	philo->eat_cont++;
	ft_precise_usleep(philo->table->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	ft_drop_forks(philo);
}
