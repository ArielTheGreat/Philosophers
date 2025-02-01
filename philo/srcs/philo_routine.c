/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:41:55 by frocha            #+#    #+#             */
/*   Updated: 2025/01/29 13:41:56 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_thread(t_philo *philo)
{
	write_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_thread(t_philo *philo)
{
	write_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	write_message(philo, "is thinking");
}

void	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	write_message(philo, "has taken a fork");
}

bool	ft_is_done(t_program *program)
{
	bool	is_done;

	pthread_mutex_lock(&program->prog_mutex);
	is_done = program->philos_done;
	pthread_mutex_unlock(&program->prog_mutex);
	return (is_done);
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (ft_philos_ready(philo->program) != true)
		;
	while (ft_monitor_ready(philo->program) != true)
		;
	if (philo->id % 2 == 0)
	{
		write_message(philo, "is thinking");
		ft_usleep(1);
	}
	while (ft_is_done(philo->program) != true)
	{
		take_fork(philo, philo->l_fork);
		take_fork(philo, philo->r_fork);
		eat_thread(philo);
		sleep_thread(philo);
	}
	return (NULL);
}
