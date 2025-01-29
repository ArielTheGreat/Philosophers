/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:07:19 by frocha            #+#    #+#             */
/*   Updated: 2025/01/29 13:07:20 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_arguments(int argc, char **argv)
{
	(void)argv;
	if (argc != 5 && argc != 6)
		error_message("Only 4 or 5 arguments are allowed\n", 1);
	if (ft_atoi(argv[1]) > 200)
		error_message("Number of philosophers cannot be bigger than 200\n", 1);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		error_message("Any number of the parameters cannot be 0 or below 0."
			" Except 5th parameter.\n", 1);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		error_message("5th parameter cannot be below 0\n", 1);
	return (0);
}

void	*start_philo_thread(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(philo->meal_lock);
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	while (1)
		philo_routine(philo);
	return (NULL);
}

int	create_threads(t_program *program, int philo_number)
{
	pthread_t	monitor_thread;
	int			i;

	i = -1;
	while (++i < philo_number)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				start_philo_thread, &program->philos[i]) != 0)
			destroy_program(program, philo_number,
				"Error: could not create thread\n");
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, program->philos) != 0)
		destroy_program(program, philo_number,
			"Error: could not create thread\n");
	if (pthread_join(monitor_thread, NULL) != 0)
		destroy_program(program, philo_number,
			"Error: could not join monitor\n");
	i = -1;
	while (++i < philo_number)
	{
		if (pthread_detach(program->philos[i].thread) != 0)
			destroy_program(program, philo_number,
				"Error: could not detach\n");
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	*program;

	program = NULL;
	if (check_arguments(argc, argv) != 0)
		return (1);
	initiate_program(&program, ft_atoi(argv[1]));
	if (!program)
		return (1);
	initialize_philos(argv, program, argc);
	create_threads(program, program->philos[0].num_of_philos);
	destroy_program(program, program->philos[0].num_of_philos, 0);
	return (0);
}
