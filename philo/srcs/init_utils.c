/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:01:28 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 08:42:29 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_init_forks(t_data **data)
{
	int	i;
	int	left;
	int	right;

	i = -1;
	while (++i < (*data)->philo_count)
	{
		(*data)->forks[i].id = i + 1;
		pthread_mutex_init(&(*data)->forks[i].mutex, NULL);
	}
	i = -1;
	while (++i < (*data)->philo_count)
	{
		left = i;
		right = (i + 1) % (*data)->philo_count;
		if (left < right)
		{
			(*data)->philos[i].first_fork = &(*data)->forks[left];
			(*data)->philos[i].second_fork = &(*data)->forks[right];
		}
		else
		{
			(*data)->philos[i].first_fork = &(*data)->forks[right];
			(*data)->philos[i].second_fork = &(*data)->forks[left];
		}
	}
}

static int	ft_init_philos(t_data **data, int i, char **argv, int argc)
{
	int	meals;

	(*data)->philos[i].data = *data;
	(*data)->philos[i].id = i + 1;
	if (((*data)->philos[i].time_to_die = ft_atoi_strict(argv[2])) <= 0
		|| ((*data)->philos[i].time_to_eat = ft_atoi_strict(argv[3])) <= 0
		|| ((*data)->philos[i].time_to_sleep = ft_atoi_strict(argv[4])) <= 0)
		return (EXIT_FAILURE);
	(*data)->philos[i].meals_required = -1;
	if (argc == 6)
	{
		meals = ft_atoi_strict(argv[5]);
		if (meals < 0)
			return (EXIT_FAILURE);
		if (meals > 0)
			(*data)->philos[i].meals_required = meals;
	}
	pthread_mutex_init(&(*data)->philos[i].meals_mutex, NULL);
	pthread_mutex_init(&(*data)->philos[i].meal_time_mutex, NULL);
	return (EXIT_SUCCESS);
}

static int	ft_init_data(t_data **data, char **argv, int argc)
{
	int	i;

	if (!(*data = ft_calloc(1, sizeof(t_data))))
		return (EXIT_FAILURE);
	if (((*data)->philo_count = ft_atoi_strict(argv[1])) <= 0
		|| (*data)->philo_count > 200)
		return (EXIT_FAILURE);
	if (!((*data)->philos = ft_calloc((*data)->philo_count, sizeof(t_philo)))
		|| !((*data)->forks = ft_calloc((*data)->philo_count, sizeof(t_fork))))
	{
		ft_clear_data(data);
		return (EXIT_FAILURE);
	}
	pthread_mutex_init(&(*data)->death_mutex, NULL);
	pthread_mutex_init(&(*data)->print_mutex, NULL);
	i = -1;
	while (++i < (*data)->philo_count)
		if (ft_init_philos(data, i, argv, argc) == EXIT_FAILURE)
			return (ft_clear_data(data), EXIT_FAILURE);
	ft_init_forks(data);
	return (EXIT_SUCCESS);
}

int	ft_init(t_data **data, char **argv, int argc)
{
	if (ft_init_data(data, argv, argc) == EXIT_FAILURE)
		return (ft_clear_data(data), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
