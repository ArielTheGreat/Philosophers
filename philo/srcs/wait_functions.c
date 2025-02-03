/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:41:37 by frocha            #+#    #+#             */
/*   Updated: 2025/02/03 16:41:38 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_wait_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}

void	wait_philosophers_ready(t_program *program)
{
	while (ft_philos_ready(program) != true)
		;
}

void	wait_monitor_ready(t_program *program)
{
	while (ft_monitor_ready(program) != true)
		;
}

bool	ft_philos_ready(t_program *program)
{
	pthread_mutex_lock(&program->prog_mutex);
	if (program->philos_ready == true)
	{
		pthread_mutex_unlock(&program->prog_mutex);
		return (true);
	}
	pthread_mutex_unlock(&program->prog_mutex);
	return (false);
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
