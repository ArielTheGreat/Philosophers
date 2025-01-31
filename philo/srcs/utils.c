/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:07:11 by frocha            #+#    #+#             */
/*   Updated: 2025/01/29 13:07:12 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	long	z;
	int		p;

	z = 0;
	p = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			p = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		z = z * 10 + (*str - '0');
		if (z > INT_MAX)
            error_message("The value is too large: MAX 2,147,483,647", 1);
		str++;
	}
	return ((int)(p * z));
}

void	write_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s\n", get_current_time() - philo->start_time,
		philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < mls)
		usleep(500);
}

void	error_message(char *text, int signal)
{
	if (text)
		write(2, text, ft_strlen(text) + 1);
	exit(signal);
}
