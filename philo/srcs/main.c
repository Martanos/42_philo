/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:59 by malee             #+#    #+#             */
/*   Updated: 2024/06/27 19:06:23 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	printf("Error please enter args this way:\n");
	printf("./philo <num_of_phils> <time_to_die> <time_to_eat> <time_to_sleep> optional:<num_of_times_each_phil_must_eat>\n");
	printf("Arguments must be valid positive integers with no special characters\n");
	exit(ERROR_CODE);
}

void	ft_check_args(char **av)
{
	char	**args_to_check;

	args_to_check = av;
	while (*args_to_check)
	{
		if (ft_is_digit(*args_to_check))
			ft_error;
		args_to_check++;
	}
}

int	main(int ac, char **av)
{
	char	**args;
	t_rules	*table;

	if (ac == 5 || ac == 6)
	{
		args = av + 1;
		ft_check_args(args);
		table = ft_init_table(args);
	}
	else
		error();
}
