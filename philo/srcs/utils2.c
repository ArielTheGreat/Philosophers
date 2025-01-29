/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:25:26 by frocha            #+#    #+#             */
/*   Updated: 2025/01/29 14:25:27 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	destroy_program(t_program *program, int number_philos, char *str)
{
	int	i;

	i = 0;
	while (i < number_philos)
	{
		pthread_mutex_destroy(&(program->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(program->meal_lock));
	pthread_mutex_destroy(&(program->write_lock));
	free(program->forks);
	free(program->philos);
	free(program);
	if (str)
		error_message(str, 1);
}
