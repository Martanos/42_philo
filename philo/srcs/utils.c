/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:27:37 by malee             #+#    #+#             */
/*   Updated: 2024/11/06 09:29:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return (result);
}

void	*ft_calloc(int64_t nmemb, int64_t size)
{
	char	*arr;
	int64_t	n;

	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	n = nmemb * size;
	while (--n)
		arr[n] = '\0';
	arr[0] = '\0';
	return ((void *)arr);
}

int64_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (EXIT_FAILURE);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	ft_precise_sleep(int64_t time_in_ms)
{
	int64_t	start;
	int64_t	elapsed;

	start = ft_get_time();
	while (1)
	{
		elapsed = ft_get_time() - start;
		if (elapsed >= time_in_ms)
			break ;
		usleep(100);
	}
}
