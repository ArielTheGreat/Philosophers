/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:06:13 by frocha            #+#    #+#             */
/*   Updated: 2025/01/29 13:06:15 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	t_program		*program;
}	t_philo;

typedef struct s_program
{
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_program;

int		ft_atoi(const char *str);
void	initialize_philos(char **argv, t_program *program, int argc);
void	initiate_program(t_program **program, int number_philos);
size_t	get_current_time(void);
void	ft_usleep(size_t mls);
void	philo_routine(t_philo *philo);
void	*monitor(void *philo_void);
void	write_message(t_philo *philo, char *str);
void	error_message(char *text, int signal);
size_t	ft_strlen(const char *s);
void	destroy_program(t_program *program, int number_philos, char *str);

#endif