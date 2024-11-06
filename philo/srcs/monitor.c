/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:48:36 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 09:55:48 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_check_death(t_data *data, int i, int64_t current_time)
{
	int64_t	time_since_last_meal;

	pthread_mutex_lock(&data->philos[i].meal_time_mutex);
	time_since_last_meal = current_time - data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].meal_time_mutex);
	if (time_since_last_meal > data->philos[i].time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
			data->someone_died = 1;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

static int	ft_check_meals_complete(t_data *data)
{
	int	j;
	int	all_complete;

	all_complete = 1;
	j = -1;
	pthread_mutex_lock(&data->death_mutex);
	while (++j < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[j].meals_mutex);
		if (data->philos[j].meals_required != -1
			&& data->philos[j].meals_eaten < data->philos[j].meals_required)
		{
			all_complete = 0;
			pthread_mutex_unlock(&data->philos[j].meals_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->philos[j].meals_mutex);
	}
	if (all_complete && !data->someone_died)
	{
		data->all_meals_complete = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (EXIT_FAILURE);
}

void	*ft_death_monitor(void *arg)
{
	t_data	*data;
	int		i;
	int64_t	current_time;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died || data->all_meals_complete)
		{
			{
				pthread_mutex_lock(&data->print_mutex);
				current_time = ft_get_time();
				printf("%ld %d died\n", current_time - data->start_time,
					data->philos->id);
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_mutex);
			i = -1;
			while (++i < data->philo_count)
			{
				current_time = ft_get_time();
				if (ft_check_death(data, i, current_time))
					return (NULL);
				if (ft_check_meals_complete(data))
					return (NULL);
			}
			usleep(1000);
		}
	}
	return (NULL);
}
