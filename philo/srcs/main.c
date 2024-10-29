/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:59 by malee             #+#    #+#             */
/*   Updated: 2024/10/30 07:00:28 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_input_checker(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				return (ft_error("Invalid input", NULL));
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_case_one(t_table *table)
{
	table->start_time = ft_get_time();
	if (pthread_create(&table->thread_id[0], NULL, &ft_routine,
			&table->philos[0]))
		return (ft_error(ERR_THREAD_CREATE, table));
	pthread_detach(table->thread_id[0]);
	while (table->dead == 0)
		ft_precise_usleep(0);
	ft_exit(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_input_checker(argv))
		return (1);
	if (ft_init(&table, argv, argc))
		return (1);
	if (table.philo_num == 1)
		return (ft_case_one(&table));
	if (ft_thread_init(&table))
		return (1);
	ft_exit(&table);
	return (0);
}
