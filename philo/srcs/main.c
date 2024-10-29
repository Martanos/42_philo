/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:59 by malee             #+#    #+#             */
/*   Updated: 2024/10/29 21:54:43 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_error(void)
{
	printf("Error please enter args as such:\n\n");
	printf("./philo <num_of_phils> <time_to_die(in ms)>\n");
	printf("<time_to_eat(in ms)> <time_to_sleep(in ms)>\n\n");
	printf("optional:<num_of_times_each_phil_must_eat(in ms)>\n\n");
	printf("Arguments must be valid POSITIVE integers\n");
	printf("Arguments must not contain special characters\n");
	exit(EXIT_FAILURE);
}

static void	ft_check_args(char **av)
{
	char	**args_to_check;

	args_to_check = av;
	while (*args_to_check)
	{
		if (ft_isdigit(*args_to_check))
			ft_error();
		if (ft_atol(*args_to_check) == -1)
			ft_error();
		if (ft_atol(*args_to_check) > INT_SIZE_MAX)
			ft_error();
		args_to_check++;
	}
}

static void	ft_cleanup(t_table **table)
{
	int	i;

	i = 0;
	while (i < (*table)->num_philos)
	{
		pthread_mutex_destroy(&(*table)->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&(*table)->write_mutex);
	pthread_mutex_destroy(&(*table)->death_mutex);
	free((*table)->forks);
	free((*table)->philosophers);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	argv++;
	if (argc < 5 || argc > 6)
		ft_error();
	ft_check_args(argv);
	table = (t_table *)ft_calloc(1, sizeof(t_table));
	(*table).num_philos = ft_atol(argv[0]);
	(*table).time_to_die = ft_atol(argv[1]);
	(*table).time_to_eat = ft_atol(argv[2]);
	(*table).time_to_sleep = ft_atol(argv[3]);
	if (argc == 6)
		(*table).meals_required = ft_atol(argv[4]);
	else
		(*table).meals_required = -1;
	if (ft_init_mutexes(&table) || ft_init_philos(&table)
		|| ft_start_simulation(&table))
	{
		printf("Failed to start simulation\n");
		return (EXIT_FAILURE);
	}
	ft_cleanup(&table);
	return (EXIT_SUCCESS);
}
