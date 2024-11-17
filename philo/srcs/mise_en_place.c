/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mise_en_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:42:39 by malee             #+#    #+#             */
/*   Updated: 2024/11/18 00:46:18 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_le_monitor(int argc, char **argv, t_monitor **monitor)
{
	(*monitor)->num_of_philos = ft_atoi_strict(argv[1]);
	(*monitor)->time_to_die = ft_atoi_strict(argv[2]);
	(*monitor)->time_to_eat = ft_atoi_strict(argv[3]);
	(*monitor)->time_to_sleep = ft_atoi_strict(argv[4]);
	if (argc == 6)
		(*monitor)->max_num_of_meals = ft_atoi_strict(argv[5]);
	else
		(*monitor)->max_num_of_meals = -1;
	pthread_mutex_init(&(*monitor)->simulation_ended_mutex, NULL);
	pthread_mutex_init(&(*monitor)->print_mutex, NULL);
}

static unsigned char	ft_le_customers(t_monitor **monitor)
{
	int	id;

	(*monitor)->philos = (t_philo *)ft_calloc((*monitor)->num_of_philos,
			sizeof(t_philo));
	if (!(*monitor)->philos)
		return (printf("Failed to allocate memory for philosophers\n"),
			EXIT_FAILURE);
	id = -1;
	while (++id < (*monitor)->num_of_philos)
	{
		(*monitor)->philos[id].monitor = *monitor;
		(*monitor)->philos[id].id = id + 1;
		(*monitor)->philos[id].owned_fork = (t_fork *)ft_calloc(1,
				sizeof(t_fork));
		if (!(*monitor)->philos[id].owned_fork)
			return (printf("Failed to allocate memory for owned fork\n"),
				EXIT_FAILURE);
		(*monitor)->philos[id].owned_fork->owner_id = id + 1;
		pthread_mutex_init(&(*monitor)->philos[id].meal_data_mutex, NULL);
		pthread_mutex_init(&(*monitor)->philos[id].full_mutex, NULL);
		pthread_mutex_init(&(*monitor)->philos[id].owned_fork->fork_mutex,
			NULL);
		pthread_mutex_init(&(*monitor)->philos[id].ready_mutex, NULL);
	}
	return (EXIT_SUCCESS);
}

// NOTE: This function is used to assign shared forks to philosophers
// NOTE: The last philosophers shared fork
// is the owned fork of the first philosopher
// NOTE: If there is only one philosopher, the shared fork is NULL
static unsigned char	ft_le_forks(t_monitor **monitor)
{
	int	id;

	if ((*monitor)->num_of_philos == 1)
		return (EXIT_SUCCESS);
	id = -1;
	while (++id < (*monitor)->num_of_philos)
		(*monitor)->philos[id].shared_fork = (*monitor)->philos[(id + 1)
			% (*monitor)->num_of_philos].owned_fork;
	return (EXIT_SUCCESS);
}

unsigned char	ft_mise_en_place(int argc, char **argv, t_monitor **monitor)
{
	*monitor = (t_monitor *)ft_calloc(1, sizeof(t_monitor));
	if (!*monitor)
		return (printf("Failed to allocate memory for monitor\n"),
			EXIT_FAILURE);
	pthread_mutex_init(&(*monitor)->all_ready_mutex, NULL);
	ft_le_monitor(argc, argv, monitor);
	if (ft_le_customers(monitor) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_le_forks(monitor) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
