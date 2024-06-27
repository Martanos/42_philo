/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:27:37 by malee             #+#    #+#             */
/*   Updated: 2024/06/27 22:43:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atol(char *str)
{
	size_t	result;

	if (!*str)
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
	return ((void *)arr);
}

size_t	ft_get_time(void)
{
	struct timeeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
