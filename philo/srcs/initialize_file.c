#include "../philo.h"

void initialize_philos(char **argv, t_program *program, int argc)
{
    int i;
    int number_philos;
    int number_times_to_eat;

    i = 0;
    if (argc == 6)
        number_times_to_eat = ft_atoi(argv[5]);
    else
        number_times_to_eat = -1;
    number_philos = ft_atoi(argv[1]);
    size_t start_time = get_current_time();
    while(i < number_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].eating = 0;
        program->philos[i].meals_eaten = 0;
        program->philos[i].num_of_philos = number_philos;
        program->philos[i].time_to_die = ft_atoi(argv[2]);
        program->philos[i].time_to_eat = ft_atoi(argv[3]);
        program->philos[i].time_to_sleep = ft_atoi(argv[4]);
        program->philos[i].num_times_to_eat = number_times_to_eat;
        program->philos[i].start_time = start_time;
        program->philos[i].last_meal = start_time;
        program->philos[i].dead = &program->dead_flag;
        program->philos[i].write_lock = &program->write_lock;
        program->philos[i].meal_lock = &program->meal_lock;
        program->philos[i].dead_lock = &program->dead_lock;
        i++;
    }
}

void inititate_program(t_program **program, int number_philos)
{
    int i;

    *program = (t_program*)malloc(sizeof(t_program));
    if (!*program)
        return;
    (*program)->dead_flag = 0;
    pthread_mutex_init(&(*program)->dead_lock, NULL);
    pthread_mutex_init(&(*program)->meal_lock, NULL);
    pthread_mutex_init(&(*program)->write_lock, NULL);
    (*program)->philos = (t_philo *)malloc(number_philos * sizeof(t_philo));
    if (!(*program)->philos)
    {
        free(*program);
        return;
    }
    pthread_mutex_t *forks = malloc(number_philos * sizeof(pthread_mutex_t));
    if (!forks)
    {
        free((*program)->philos);
        free(*program);
        return;
    }
    i = 0;
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