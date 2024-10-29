/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:01:28 by malee             #+#    #+#             */
/*   Updated: 2024/10/30 07:48:40 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_init_table(t_table *table)
{
	table->thread_id = ft_calloc(table->philo_num, sizeof(pthread_t));
	if (!table->thread_id)
		return (ft_error(ALLOC_ERR_THREAD, table));
	table->forks = ft_calloc(table->philo_num, sizeof(pthread_mutex_t));
	if (!table->forks)
		return (ft_error(ALLOC_ERR_PHILO, table));
	table->philos = ft_calloc(table->philo_num, sizeof(t_philo));
	if (!table->philos)
		return (ft_error(ALLOC_ERR_PHILO, table));
	return (0);
}

int	ft_init_forks(t_table *table)
{
	ssize_t	i;
	size_t	left;
	size_t	right;

	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_init(&table->forks[i], NULL);
	i = 0;
	while (i < table->philo_num)
	{
		left = i;
		right = (i + 1) % table->philo_num;
		if (left < right)
		{
			table->philos[i].left_fork = &table->forks[left];
			table->philos[i].right_fork = &table->forks[right];
		}
		else
		{
			table->philos[i].left_fork = &table->forks[right];
			table->philos[i].right_fork = &table->forks[left];
		}
		i++;
	}
	return (0);
}

void	ft_init_philos(t_table *table)
{
	ssize_t	i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].time_to_die = table->death_time;
		table->philos[i].eat_cont = 0;
		table->philos[i].eating = 0;
		table->philos[i].status = 0;
		pthread_mutex_init(&table->philos[i].lock, NULL);
		i++;
	}
}

int	ft_init_data(t_table *table, char **argv, int argc)
{
	table->philo_num = ft_atoi_strict(argv[1]);
	table->death_time = ft_atoi_strict(argv[2]);
	table->eat_time = ft_atoi_strict(argv[3]);
	table->sleep_time = ft_atoi_strict(argv[4]);
	if (argc == 6)
		table->meals_num = ft_atoi_strict(argv[5]);
	else
		table->meals_num = -1;
	if (table->philo_num <= 0 || table->philo_num > 200 || table->death_time < 0
		|| table->eat_time < 0 || table->sleep_time < 0)
		return (ft_error("Invalid input", NULL));
	table->dead = 0;
	table->finished = 0;
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->lock, NULL);
	return (0);
}

int	ft_init(t_table *table, char **argv, int argc)
{
	if (ft_init_data(table, argv, argc))
		return (1);
	if (ft_init_table(table))
		return (1);
	if (ft_init_forks(table))
		return (1);
	ft_init_philos(table);
	return (0);
}
