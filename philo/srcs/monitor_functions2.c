/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:00:03 by frocha            #+#    #+#             */
/*   Updated: 2025/02/02 13:00:05 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	all_philo_ate(t_philo *philos)
{
	int	i;
	int	finished;

	if (philos[0].num_times_to_eat == -1)
		return (0);
	i = 0;
	finished = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished == philos[0].num_of_philos)
		return (1);
	return (0);
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

void	wait_philosophers_ready(t_program *program)
{
	while (ft_philos_ready(program) != true)
		;
}
