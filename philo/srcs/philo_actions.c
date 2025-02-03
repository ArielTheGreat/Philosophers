/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:58:18 by frocha            #+#    #+#             */
/*   Updated: 2025/02/03 16:58:19 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_thread(t_philo *philo)
{
	if (philo->meals_eaten >= philo->num_times_to_eat
		&& philo->num_times_to_eat != -1)
		return ;
	pthread_mutex_lock(philo->l_fork);
	write_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	write_message(philo, "has taken a fork");
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
