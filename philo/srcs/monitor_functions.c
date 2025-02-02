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

void	initialize_monitor(t_program *program)
{
	wait_philosophers_ready(program);
	pthread_mutex_lock(&program->prog_mutex);
	program->start_time = get_current_time();
	pthread_mutex_unlock(&program->prog_mutex);
	ft_set_last_meal(program);
	pthread_mutex_lock(&program->prog_mutex);
	program->monitor_ready = true;
	pthread_mutex_unlock(&program->prog_mutex);
}

bool	check_single_philosopher(t_philo *philo, t_program *program)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(philo->meal_lock);
	time_since_last_meal = get_current_time() - philo->last_meal;
	if (time_since_last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&program->prog_mutex);
		program->philos_done = true;
		pthread_mutex_unlock(&program->prog_mutex);
		pthread_mutex_lock(philo->write_lock);
		printf("%zu %d %s\n",
			get_current_time() - program->start_time,
			philo->id, "died");
		pthread_mutex_unlock(philo->write_lock);
		pthread_mutex_unlock(philo->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

void	*monitor(void *philo_void)
{
	t_philo		*philos;
	t_program	*program;
	int			i;

	philos = (t_philo *)philo_void;
	program = philos[0].program;
	initialize_monitor(program);
	while (1)
	{
		i = 0;
		while (i < philos[0].num_of_philos)
		{
			if (check_single_philosopher(&philos[i], program))
				return (NULL);
			i++;
		}
		if (all_philo_ate(philos) == 1)
		{
			pthread_mutex_lock(&program->prog_mutex);
			program->philos_done = true;
			pthread_mutex_unlock(&program->prog_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
