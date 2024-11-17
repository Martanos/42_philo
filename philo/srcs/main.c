/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:43:17 by malee             #+#    #+#             */
/*   Updated: 2024/11/17 22:29:36 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_monitor	*monitor;

	monitor = NULL;
	if (ft_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_mise_en_place(argc, argv, &monitor) == EXIT_FAILURE)
	{
		ft_cleanup(&monitor);
		return (EXIT_FAILURE);
	}
	ft_simulation(&monitor);
	ft_cleanup(&monitor);
	return (EXIT_SUCCESS);
}
