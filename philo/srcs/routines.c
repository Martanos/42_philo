/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:53:58 by malee             #+#    #+#             */
/*   Updated: 2024/10/29 22:00:34 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		died;

	philo = (t_philo *)arg;
	while (philo->table->start_time == 0)
		usleep(100);
	philo->last_meal_time = philo->table->start_time;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		died = philo->table->someone_died;
		pthread_mutex_unlock(&philo->table->death_mutex);
		if (died)
			break ;
		ft_eat(&philo);
		if (philo->table->meals_required > 0
			&& philo->meals_eaten == philo->table->meals_required)
			break ;
	}
	return (NULL);
}

void	ft_reaper_routine(t_table **table)
{
	int		i;
	t_philo	*current;

	while (!(*table)->someone_died)
	{
		i = 0;
		while (i < (*table)->num_philos)
		{
			current = &((*table)->philosophers[i]);
			if (ft_check_death(&current))
				return ;
			if ((*table)->meals_required != -1)
			{
				if ((*table)->philosophers[i].meals_eaten < (*table)->meals_required
					|| i == (*table)->num_philos - 1)
					break ;
			}
			i++;
		}
		usleep(100);
	}
}

static void	ft_eat(t_philo **philo)
{
	long long	start_eat_time;

	pthread_mutex_lock((*philo)->left_fork);
	ft_print_status(philo, "has taken a fork");
	pthread_mutex_lock((*philo)->right_fork);
	ft_print_status(philo, "has taken a fork");
	start_eat_time = ft_get_time();
	ft_print_status(philo, "is eating");
	(*philo)->last_meal_time = ft_get_time();
	(*philo)->meals_eaten++;
	while (ft_get_time() - start_eat_time < (*philo)->table->time_to_eat)
		usleep(500);
	pthread_mutex_unlock((*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
}

static void	ft_think_sleep(t_philo **philo)
{
	long long	start_sleep_time;

	ft_print_status(philo, "is sleeping");
	start_sleep_time = ft_get_time();
	while (ft_get_time() - start_sleep_time < (*philo)->table->time_to_sleep)
		usleep(500);
	ft_print_status(philo, "is thinking");
}

int	ft_check_death(t_philo **philo)
{
	long long	current_time;

	current_time = ft_get_time();
	if ((current_time
			- (*philo)->last_meal_time) > (*philo)->table->time_to_die)
	{
		pthread_mutex_lock(&(*philo)->table->death_mutex);
		(*philo)->table->someone_died = 1;
		pthread_mutex_unlock(&(*philo)->table->death_mutex);
		ft_print_status(philo, "died");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
