/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:49:06 by frocha            #+#    #+#             */
/*   Updated: 2025/02/03 16:49:07 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_init_philo(t_program *program, int i)
{
	if (pthread_create(&program->philos[i].thread, NULL,
			philo_routine, &program->philos[i]) != 0)
		destroy_program(program,
			"Error: could not create thread\n");
}

void	ft_monitor_init(t_program *program)
{
	if (pthread_create(&program->monitor, NULL, &monitor, program->philos) != 0)
		destroy_program(program,
			"Error: could not create thread\n");
}

int	create_threads(t_program *program)
{
	int			i;

	i = -1;
	pthread_mutex_init(&program->prog_mutex, NULL);
	ft_monitor_init(program);
	while (++i < program->num_philos)
		ft_init_philo(program, i);
	pthread_mutex_lock(&program->prog_mutex);
	program->philos_ready = true;
	pthread_mutex_unlock(&program->prog_mutex);
	ft_wait_philos(program);
	pthread_join(program->monitor, NULL);
	return (0);
}
