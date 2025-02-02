/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:43:22 by frocha            #+#    #+#             */
/*   Updated: 2025/01/29 13:43:23 by frocha           ###   ########.fr       */
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

void wait_philosophers_ready(t_program *program)
{
	while(program->philos_ready != true)
		;
}

int	ft_set_last_meal(t_program *program)
{
	int		i;
	t_philo	*philos;
                                                                                                      
	i = 0;
	philos = program->philos;
	while (i < program->num_philos)
	{
		pthread_mutex_lock(&program->meal_lock);
		philos[i].last_meal = program->start_time;
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	return (0);
}

void	*monitor(void *philo_void)
{
	t_philo	*philos;
	t_program *program;
	int		i;
	size_t	time_since_last_meal;

	philos = (t_philo *)philo_void;
	program = philos[0].program;
	wait_philosophers_ready(program);
	pthread_mutex_lock(&program->prog_mutex);
	program->start_time = get_current_time();
	pthread_mutex_unlock(&program->prog_mutex);
	ft_set_last_meal(program);
	program->monitor_ready = true;
	while (1)
	{
		i = 0;
		while (i < philos[0].num_of_philos)
		{
			pthread_mutex_lock(philos[i].meal_lock);
			time_since_last_meal = get_current_time() - philos[i].last_meal;
			if (time_since_last_meal > philos[i].time_to_die)
			{
				program->philos_done = true;
				pthread_mutex_lock(philos[i].write_lock);
				printf("%zu %d %s\n", get_current_time() - program->start_time,
					philos[i].id, "died");
				pthread_mutex_unlock(philos[i].write_lock);
				pthread_mutex_unlock(philos[i].meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(philos[i].meal_lock);
			i++;
		}
		if (all_philo_ate(philos) == 1)
		{
			program->philos_done = true;
			return (NULL);
		}
	}
	return (NULL);
}
