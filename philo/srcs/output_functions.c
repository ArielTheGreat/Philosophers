/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:45:32 by frocha            #+#    #+#             */
/*   Updated: 2025/02/03 16:45:33 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_message(char *text, int signal)
{
	if (text)
		write(2, text, ft_strlen(text) + 1);
	exit(signal);
}

void	write_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->program->prog_mutex);
	if (philo->program->philos_done)
	{
		pthread_mutex_unlock(&philo->program->prog_mutex);
		return ;
	}
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_unlock(&philo->program->prog_mutex);
	printf("%zu %d %s\n", get_current_time() - philo->program->start_time,
		philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}
