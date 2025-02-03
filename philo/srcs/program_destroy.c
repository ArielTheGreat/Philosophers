/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:54:48 by frocha            #+#    #+#             */
/*   Updated: 2025/02/03 16:54:50 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
