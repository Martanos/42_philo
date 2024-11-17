/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:43:55 by malee             #+#    #+#             */
/*   Updated: 2024/11/18 01:39:21 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// NOTE: This function is used to convert a string to an integer
// NOTE: It returns -1 if the string is not a valid integer
int64_t	ft_atoi_strict(char *str)
{
	int64_t	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX || result < 0 || result == 0)
			return (-1);
		i++;
	}
	return (result);
}

// NOTE: This function is used to allocate memory and initialize it to 0
void	*ft_calloc(int64_t nmemb, int64_t size)
{
	void	*ptr;
	char	*temp;
	int64_t	total_size;
	int64_t	i;

	if (nmemb > 0 && size > INT64_MAX / nmemb)
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	temp = (char *)ptr;
	i = -1;
	while (++i < total_size)
		temp[i] = 0;
	return (ptr);
}

// NOTE: This function is used to sleep for a precise amount of time
void	ft_precise_sleep(int64_t time_in_ms)
{
	int64_t	start;
	int64_t	elapsed;
	int64_t	remaining;

	start = ft_get_time();
	while (1)
	{
		elapsed = ft_get_time() - start;
		if (elapsed >= time_in_ms)
			break ;
		remaining = time_in_ms - elapsed;
		if (remaining > 2)
			usleep(remaining * 50);
		else
			usleep(50);
	}
}

void	ft_print_message(t_philo **philo, char *message)
{
	int64_t	current_time;
	int64_t	relative_time;

	pthread_mutex_lock(&(*philo)->monitor->simulation_ended_mutex);
	if ((*philo)->monitor->simulation_ended == true)
	{
		pthread_mutex_unlock(&(*philo)->monitor->simulation_ended_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&(*philo)->monitor->simulation_ended_mutex);
	current_time = ft_get_time();
	relative_time = current_time - (*philo)->monitor->start_time;
	pthread_mutex_lock(&(*philo)->monitor->print_mutex);
	printf("%ld %d %s\n", relative_time, (*philo)->id, message);
	pthread_mutex_unlock(&(*philo)->monitor->print_mutex);
}
