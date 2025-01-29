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

void	philo_routine(t_philo *philo)
{
	take_fork(philo, philo->l_fork);
	take_fork(philo, philo->r_fork);
	eat_thread(philo);
	sleep_thread(philo);
}
