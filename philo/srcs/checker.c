/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:51:50 by malee             #+#    #+#             */
/*   Updated: 2024/11/17 22:29:26 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_input_checker(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

unsigned char	ft_checker(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments\n"), EXIT_FAILURE);
	if (ft_input_checker(argv) == EXIT_FAILURE)
		return (printf("Invalid input\n"), EXIT_FAILURE);
	if (ft_atoi_strict(argv[1]) == -1)
		return (printf("Invalid number of philosophers\n"), EXIT_FAILURE);
	if (ft_atoi_strict(argv[2]) == -1)
		return (printf("Invalid time to die\n"), EXIT_FAILURE);
	if (ft_atoi_strict(argv[3]) == -1)
		return (printf("Invalid time to eat\n"), EXIT_FAILURE);
	if (ft_atoi_strict(argv[4]) == -1)
		return (printf("Invalid time to sleep\n"), EXIT_FAILURE);
	if (argc == 6 && ft_atoi_strict(argv[5]) == -1)
		return (printf("Invalid number of times each philosopher must eat\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
