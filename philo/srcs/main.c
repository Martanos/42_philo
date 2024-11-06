/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:59 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 07:22:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_input_checker(char **argv)
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
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments\n"), EXIT_FAILURE);
	if (ft_input_checker(argv) == EXIT_FAILURE)
		return (printf("Invalid input\n"), EXIT_FAILURE);
	if (ft_init(&data, argv, argc) == EXIT_FAILURE)
		return (printf("Invalid input\n"), EXIT_FAILURE);
	ft_routine_loop(&data);
	ft_clear_data(&data);
	return (0);
}
