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
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_program	t_program;
typedef pthread_mutex_t		t_mutex;
typedef pthread_t			t_thread;

typedef struct s_philo
{
	t_thread		thread;
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
	t_mutex			*r_fork;
	t_mutex			*l_fork;
	t_mutex			*write_lock;
	t_mutex			*meal_lock;
	t_program		*program;
}	t_philo;

typedef struct s_program
{
	int				num_philos;
	t_mutex			meal_lock;
	t_mutex			prog_mutex;
	t_mutex			write_lock;
	t_mutex			*forks;
	t_thread		monitor;
	bool			philos_ready;
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