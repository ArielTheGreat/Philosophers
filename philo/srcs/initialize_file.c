/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:07:27 by frocha            #+#    #+#             */
/*   Updated: 2025/01/29 13:07:29 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	initialize_philos(char **argv, t_program *program, int argc)
{
	int		i;
	int		number_philos;

	i = 0;
	number_philos = ft_atoi(argv[1]);
	while (i < number_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		program->philos[i].num_of_philos = number_philos;
		program->philos[i].time_to_die = ft_atoi(argv[2]);
		program->philos[i].time_to_eat = ft_atoi(argv[3]);
		program->philos[i].time_to_sleep = ft_atoi(argv[4]);
		program->philos[i].start_time = get_current_time();
		program->philos[i].last_meal = get_current_time();
		program->philos[i].num_times_to_eat = -1;
		if (argc == 6)
			program->philos[i].num_times_to_eat = ft_atoi(argv[5]);
		program->philos[i].write_lock = &(program->write_lock);
		program->philos[i].meal_lock = &(program->meal_lock);
		program->philos[i].program = program;
		i++;
	}
}

void	set_mutex_forks(t_program **program, int number_philos)
{
	int		i;
	t_mutex *forks;

	i = 0;
	forks = (*program)->forks;
	while (i < number_philos)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < number_philos)
	{
		(*program)->philos[i].l_fork = &forks[i];
		(*program)->philos[i].r_fork = &forks[(i + 1) % number_philos];
		i++;
	}
}

void	initiate_program(t_program **program, int number_philos)
{
	*program = (t_program *)malloc(sizeof(t_program));
	if (!*program)
		return ;
	(*program)->num_philos = number_philos;
	(*program)->philos_ready = false;
	pthread_mutex_init(&(*program)->meal_lock, NULL);
	pthread_mutex_init(&(*program)->write_lock, NULL);
	pthread_mutex_init(&(*program)->prog_mutex, NULL);
	(*program)->philos = (t_philo *)malloc(number_philos * sizeof(t_philo));
	if (!(*program)->philos)
	{
		free(*program);
		return ;
	}
	(*program)->forks = malloc(number_philos * sizeof(t_mutex));
	if (!(*program)->forks)
	{
		free((*program)->philos);
		free(*program);
		return ;
	}
	set_mutex_forks(program, number_philos);
}
