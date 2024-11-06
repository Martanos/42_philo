/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:48:36 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 08:15:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_check_death(t_data *data, int i, int64_t current_time)
{
	pthread_mutex_lock(data->philos[i].meal_time_mutex);
	if (current_time
		- data->philos[i].last_meal_time > data->philos[i].time_to_die)
	{
		pthread_mutex_unlock(data->philos[i].meal_time_mutex);
		if (!data->someone_died)
		{
			data->someone_died = 1;
			ft_print_status(&data->philos[i], "died");
		}
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(data->philos[i].meal_time_mutex);
	return (EXIT_FAILURE);
}

static int	ft_check_meals_complete(t_data *data)
{
	int	j;
	int	all_complete;

	all_complete = 1;
	j = -1;
	while (++j < data->philo_count)
	{
		pthread_mutex_lock(data->philos[j].meals_mutex);
		if (data->philos[j].meals_eaten < data->philos[j].meals_required)
		{
			all_complete = 0;
			pthread_mutex_unlock(data->philos[j].meals_mutex);
			break ;
		}
		pthread_mutex_unlock(data->philos[j].meals_mutex);
	}
	if (all_complete)
	{
		data->all_meals_complete = 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int	ft_monitor_meals(t_data *data, int i)
{
	pthread_mutex_lock(data->philos[i].meals_mutex);
	if (data->philos[i].meals_required == -1)
	{
		pthread_mutex_unlock(data->philos[i].meals_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(data->philos[i].meals_mutex);
	return (ft_check_meals_complete(data));
}

void	*ft_death_monitor(void *arg)
{
	t_data	*data;
	int		i;
	int64_t	current_time;

	data = (t_data *)arg;
	while (!data->someone_died && !data->all_meals_complete)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			current_time = ft_get_time();
			pthread_mutex_lock(data->death_mutex);
			if (ft_check_death(data, i, current_time) == EXIT_SUCCESS
				|| ft_monitor_meals(data, i) == EXIT_SUCCESS)
			{
				pthread_mutex_unlock(data->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(data->death_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
