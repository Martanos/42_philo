/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:27:37 by malee             #+#    #+#             */
/*   Updated: 2024/10/29 19:55:12 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	ft_atol(char *str)
{
	long long	result;

	result = 0;
	if (!str)
		return (-1);
	while (*str && ((*str == 32) || (*str >= 7 && *str <= 13)))
		str++;
	if (*str && (*str == '-' || *str == '+'))
		return (-1);
	while (*str && *str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result);
}

int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}

void	*ft_calloc(ssize_t nmemb, ssize_t size)
{
	char	*arr;
	ssize_t	n;

	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	n = nmemb * size;
	while (--n)
		arr[n] = '\0';
	arr[0] = '\0';
	return ((void *)arr);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->table->write_mutex);
	time = ft_get_time() - philo->table->start_time;
	if (!philo->table->someone_died)
		printf("%lld %lld %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
