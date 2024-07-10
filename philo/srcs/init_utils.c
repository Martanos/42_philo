/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:01:28 by malee             #+#    #+#             */
/*   Updated: 2024/07/10 15:59:52 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phil	*ft_init_table(char **args)
{
	t_rules	*rules;
	t_phil	*phils;

	rules = ft_init_rules(args);
	phils = ft_init_phils(rules, 1);
	return (phils);
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
		new_node->rules = rules;
		pthread_mutex_init(&(new_node->left_fork), NULL);
		pthread_mutex_init(&(new_node->set_is_eating), NULL);
		pthread_mutex_init(&(new_node->set_time_last_eaten), NULL);
		pthread_mutex_init(&(new_node->set_meals_eaten), NULL);
		if (start++ == 1)
			phils = new_node;
		else
		{
			current->right_fork = &(new_node->left_fork);
			current->next_phil = new_node;
		}
		current = new_node;
	}
	current->right_fork = &(phils->left_fork);
	current->next_phil = phils;
	return (phils);
}

t_rules	*ft_init_rules(char **args)
{
	t_rules	*rules;

	rules = ft_calloc(1, sizeof(t_rules));
	rules->num_of_phils = ft_atol(args[0]);
	rules->time_to_die = ft_atol(args[1]);
	rules->time_to_eat = ft_atol(args[2]);
	rules->time_to_sleep = ft_atol(args[3]);
	if (ft_atol(args[4]) != -1)
		rules->max_meals = ft_atol(args[4]);
	else
		rules->max_meals = -1;
	pthread_mutex_init(&(rules->is_printing), NULL);
	pthread_mutex_init(&(rules->set_dead_phil), NULL);
	return (rules);
}

void	ft_clear_tables(t_phil *phils)
{
	t_phil	*current;
	t_phil	*next;
	ssize_t	i;
	ssize_t	j;

	current = phils;
	j = phils->rules->num_of_phils;
	i = 0;
	pthread_mutex_destroy(&(phils->rules->set_dead_phil));
	pthread_mutex_destroy(&(phils->rules->is_printing));
	free(phils->rules);
	while (i < j)
	{
		next = current->next_phil;
		pthread_mutex_destroy(&(current->left_fork));
		pthread_mutex_destroy(&(current->set_time_last_eaten));
		pthread_mutex_destroy(&(current->set_is_eating));
		pthread_mutex_destroy(&(current->set_meals_eaten));
		free(current);
		current = next;
		i++;
	}
}
