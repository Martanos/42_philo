/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:01:28 by malee             #+#    #+#             */
/*   Updated: 2024/07/08 22:42:39 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phil	*ft_init_table(char **args)
{
	t_rules	*rules;

	rules = ft_init_rules(args);
	return (ft_init_phils(rules, 1));
}

t_phil	*ft_init_phils(t_rules *rules, ssize_t start)
{
	t_phil	*new_node;
	t_phil	*current;
	t_phil	*phils;

	while (start <= rules->num_of_phils)
	{
		new_node = ft_calloc(1, sizeof(t_phil));
		new_node->id = start;
		new_node->rules = &rules;
		pthread_mutex_init(&(new_node->left_fork), NULL);
		pthread_mutex_init(&(new_node->set_is_eating), NULL);
		pthread_mutex_init(&(new_node->set_time_last_eaten), NULL);
		if (start == 1)
			phils = new_node;
		else
		{
			current->right_fork = &(new_node->left_fork);
			current->next_phil = new_node;
		}
		current = new_node;
		start++;
	}
	current->right_fork = &(phils->left_fork);
	current->next_phil = phils;
	return (phils);
}

t_rules	*ft_init_rules(char **args)
{
	t_rules	*rules;

	pthread_mutex_init(&(rules->set_dead_phil), NULL);
	rules = calloc(1, sizeof(t_rules));
	rules->num_of_phils = ft_atol(args[0]);
	rules->time_to_die = ft_atol(args[1]);
	rules->time_to_eat = ft_atol(args[2]);
	rules->time_to_sleep = ft_atol(args[3]);
	if (ft_atol(args[4]) != -1)
		rules->max_meals = ft_atol(args[4]);
	else
		rules->max_meals = -1;
	pthread_mutex_init(&(rules->is_printing), NULL);
	return (rules);
}

void	ft_clear_table(t_phil *phils)
{
	// TODO
}
