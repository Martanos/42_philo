/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:59 by malee             #+#    #+#             */
/*   Updated: 2024/07/10 17:56:34 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	printf("Error please enter args this way:\n");
	printf("./philo <num_of_phils> <time_to_die(in ms)>\n");
	printf(" <time_to_eat(in ms)> <time_to_sleep(in ms)>\n");
	printf("optional:<num_of_times_each_phil_must_eat(in ms)>\n");
	printf("Arguments must be valid\n");
	printf("positive integers with no special characters\n");
	exit(ERROR_CODE);
}

void	ft_check_args(char **av)
{
	char	**args_to_check;

	args_to_check = av;
	while (*args_to_check)
	{
		if (ft_isdigit(*args_to_check))
			ft_error();
		else if (ft_atol(*args_to_check) == -1)
			ft_error();
		else if (ft_atol(*args_to_check) > SIZE_MAX)
			ft_error();
		args_to_check++;
	}
}

int	main(int ac, char **av)
{
	char	**args;
	t_phil	*phils;

	if (ac == 5 || ac == 6)
	{
		args = av + 1;
		ft_check_args(args);
		phils = ft_init_table(args);
		ft_mise_en_place(phils);
		ft_clear_tables(phils);
	}
	else
		ft_error();
}
