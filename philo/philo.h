#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct philo
{
    pthread_t   thread;
    int         id;
    int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
    pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
    pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}   t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

int	ft_atoi(const char *str);
void initialize_philos(char **argv, t_program *program, int argc);
void inititate_program(t_program **program, int number_philos);
size_t get_current_time();

#endif
