/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:01:28 by malee             #+#    #+#             */
/*   Updated: 2024/06/27 19:04:20 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	*ft_init_table(char **args)
{
	t_rules	*table;

	table = calloc(1, sizeof(t_rules));
	table->time_to_die = ft_atol(args[1]);
	table->time_to_eat = ft_atol(args[2]);
	table->time_to_sleep = ft_atol(args[3]);
	if (ft_atol(args[4]) != -1)
		table->max_meals = ft_atol(args[4]);
	else
		table->max_meals = -1;
	pthread_mutex_init(&(table->is_printing), NULL);
	ft_init_phils(table, ft_atol(args[0]), 1);
	return (table);
}

void	ft_init_phils(t_rules *table, size_t num_phils, size_t start)
{
	t_phil	*current;
	t_phil	*first;

	first = NULL;
	while (start <= num_phils)
	{
		current = calloc(1, sizeof(t_phil));
		current->id = start;
		pthread_mutex_init(&(current->left_fork), NULL);
		if (start == 1)
		{
			table->phils = current;
			first = current;
		}
		else
		{
			current->right_fork = &(table->phils->left_fork);
			table->phils->next_phil = current;
			table->phils = current;
		}
		start++;
	}
	table->phils->next_phil = first;
	first->right_fork = &(table->phils->left_fork);
}
