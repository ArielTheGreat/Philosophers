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
	size_t			start_time;
	t_mutex			prog_mutex;
	t_mutex			write_lock;
	t_mutex			*forks;
	t_thread		monitor;
	bool			philos_ready;
	bool			monitor_ready;
	bool			philos_done;
	t_philo			*philos;
}	t_program;

/* utils.c */
int		ft_atoi(const char *str);
size_t	get_current_time(void);
void	ft_usleep(size_t mls);
size_t	ft_strlen(const char *s);

/* initialize_file.c */
void	initiate_program(t_program **program, int number_philos);
void	initialize_philos(char **argv, t_program *program, int argc);

/* monitor_functions.c */
void	*monitor(void *philo_void);

/* thread_creator.c */
void	ft_init_philo(t_program *program, int i);
void	ft_monitor_init(t_program *program);
int		create_threads(t_program *program);

/* program_destroy.c */
void	destroy_program(t_program *program, char *str);

/* output_functions.c */
void	write_message(t_philo *philo, char *str);
void	error_message(char *text, int signal);

/* philo_routine.c */
void	*philo_routine(void *philo_done);

/* wait_functions.c */
void	wait_philosophers_ready(t_program *program);
void	wait_monitor_ready(t_program *program);
void	ft_wait_philos(t_program *program);
bool	ft_philos_ready(t_program *program);
bool	ft_monitor_ready(t_program *program);

/* philo_actions.c */
void	eat_thread(t_philo *philo);
void	sleep_thread(t_philo *philo);

/* monitor_functions2.c */
int		all_philo_ate(t_philo *philos);

#endif