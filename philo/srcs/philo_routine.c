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

bool	ft_is_done(t_program *program)
{
	bool	is_done;

	pthread_mutex_lock(&program->prog_mutex);
	is_done = program->philos_done;
	pthread_mutex_unlock(&program->prog_mutex);
	return (is_done);
}

void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	write_message(philo, "has taken a fork");
	pthread_mutex_unlock(philo->l_fork);
	return ;
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (ft_philos_ready(philo->program) != true)
		;
	while (ft_monitor_ready(philo->program) != true)
		;
	if (philo->program->num_philos == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
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
