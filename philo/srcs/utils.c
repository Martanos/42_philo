/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:27:37 by malee             #+#    #+#             */
/*   Updated: 2024/10/30 07:27:56 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

ssize_t	ft_atoi_strict(char *str)
{
	ssize_t	result;
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
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return (result);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;
	size_t	n;

	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	n = nmemb * size;
	while (--n)
		arr[n] = '\0';
	arr[0] = '\0';
	return ((void *)arr);
}

ssize_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (ssize_t)1000) + (tv.tv_usec / 1000));
}

void	ft_precise_usleep(ssize_t time)
{
	ssize_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(time / 10);
}

void	ft_print_status(char *str, t_philo *philo)
{
	ssize_t	time;

	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->dead && ft_strcmp(DIED, str) != 0)
	{
		pthread_mutex_unlock(&philo->table->lock);
		return ;
	}
	pthread_mutex_lock(&philo->table->write);
	time = ft_get_time() - philo->table->start_time;
	if (ft_strcmp(DIED, str) == 0)
	{
		printf("%ld %ld %s\n", time, philo->philo_id, str);
		philo->table->dead = 1;
	}
	else
		printf("%ld %ld %s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->table->write);
	pthread_mutex_unlock(&philo->table->lock);
}
