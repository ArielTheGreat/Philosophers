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

void	destroy_program(t_program *program, char *str)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		pthread_mutex_destroy(&(program->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(program->meal_lock));
	pthread_mutex_destroy(&(program->write_lock));
	pthread_mutex_destroy(&(program->prog_mutex));
	free(program->forks);
	free(program->philos);
	free(program);
	if (str)
		error_message(str, 1);
}

bool	ft_monitor_ready(t_program *program)
{
	pthread_mutex_lock(&program->prog_mutex);
	if (program->monitor_ready == true)
	{
		pthread_mutex_unlock(&program->prog_mutex);
		return (true);
	}
	pthread_mutex_unlock(&program->prog_mutex);
	return (false);
}

void	ft_monitor_init(t_program *program)
{
	if (pthread_create(&program->monitor, NULL, &monitor, program->philos) != 0)
		destroy_program(program,
			"Error: could not create thread\n");
}
