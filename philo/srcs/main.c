
#include "../philo.h"

void *monitor(void *program_void);

int check_arguments(int argc, char **argv)
{
    (void)argv;
    if (argc != 5 && argc != 6)
    {
        printf("Only 4 or 5 arguments are allowed");
        return (1);
    }
    if (ft_atoi(argv[1]) > 200)
    {
        printf("Number of philosophers cannot be bigger than 200");
        return (1);
    }
    if(ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
    {
        printf("Any number of the parameters cannot be 0 or below 0. Except 5ft parameter.");
        return (1);
    }
    if (argc == 6 && ft_atoi(argv[5]) < 0)
    {
        printf("5ft parameter cannot be below 0");
        return (1);
    }
    return (0);
}

void *philo_update(void *philo_void)
{
    t_philo *philo = (t_philo *)philo_void;

    while (1)
    {
        pthread_mutex_lock(philo->dead_lock);
        if (*philo->dead == 1)
        {
            pthread_mutex_unlock(philo->dead_lock);
            break;
        }
        pthread_mutex_unlock(philo->dead_lock);
        if (philo->id % 2 == 0)
        {
            usleep(1000);
            pthread_mutex_lock(philo->dead_lock);
            if (*philo->dead == 1)
            {
                pthread_mutex_unlock(philo->dead_lock);
                break;
            }
            pthread_mutex_unlock(philo->dead_lock);
            pthread_mutex_lock(philo->l_fork);
            pthread_mutex_lock(philo->write_lock);
            printf("%zu Philosopher %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
            pthread_mutex_unlock(philo->write_lock);
            pthread_mutex_lock(philo->dead_lock);
            if (*philo->dead == 1)
            {
                pthread_mutex_unlock(philo->dead_lock);
                break;
            }
            pthread_mutex_unlock(philo->dead_lock);
            pthread_mutex_lock(philo->r_fork);
            pthread_mutex_lock(philo->write_lock);
            printf("%zu Philosopher %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
            pthread_mutex_unlock(philo->write_lock);
        }
        else
        {
            pthread_mutex_lock(philo->dead_lock);
            if (*philo->dead == 1)
            {
                pthread_mutex_unlock(philo->dead_lock);
                break;
            }
            pthread_mutex_unlock(philo->dead_lock);
            pthread_mutex_lock(philo->r_fork);
            pthread_mutex_lock(philo->write_lock);
            printf("%zu Philosopher %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
            pthread_mutex_unlock(philo->write_lock);
            if (philo->r_fork == philo->l_fork)
            {
                usleep(philo->time_to_die*1000);
            }else{
                pthread_mutex_lock(philo->l_fork);
                pthread_mutex_lock(philo->write_lock);
                printf("%zu Philosopher %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
                pthread_mutex_unlock(philo->write_lock);
            }
        }
        pthread_mutex_lock(philo->dead_lock);
        if (*philo->dead == 1)
        {
            pthread_mutex_unlock(philo->dead_lock);
            pthread_mutex_unlock(philo->l_fork);
            pthread_mutex_unlock(philo->r_fork);
            break;
        }
        pthread_mutex_unlock(philo->dead_lock);
        pthread_mutex_lock(philo->meal_lock);
        philo->last_meal = get_current_time();
        philo->meals_eaten++;
        pthread_mutex_unlock(philo->meal_lock);
        printf("%zu Philosopher %d is eating\n", get_current_time() - philo->start_time, philo->id);
        usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_lock(philo->dead_lock);
        if (*philo->dead == 1)
        {
            pthread_mutex_unlock(philo->dead_lock);
            break;
        }
        pthread_mutex_unlock(philo->dead_lock);
        printf("%zu Philosopher %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
        usleep(philo->time_to_sleep * 1000);
    }
    return NULL;
}

void create_philo_threads(t_program *program)
{
    int i;

    i = 0;
    while (i < program->philos[0].num_of_philos)
    {
        pthread_create(&program->philos[i].thread, NULL, philo_update, &program->philos[i]);
        i++;
    }
}

void join_philo_threads(t_program *program)
{
    int i;

    i = 0;
    while (i < program->philos[0].num_of_philos)
    {
        pthread_join(program->philos[i].thread, NULL);
        i++;
    }
}

void *monitor(void *program_void)
{
    t_program *program = (t_program *)program_void;
    int i;
    size_t current_time;
    size_t time_since_last_meal;
    int all_philosophers_ate_enough;

    while (1)
    {
        all_philosophers_ate_enough = 1;
        for (i = 0; i < program->philos[0].num_of_philos; i++)
        {
            pthread_mutex_lock(&program->meal_lock);
            current_time = get_current_time();
            time_since_last_meal = current_time - program->philos[i].last_meal;
            if (time_since_last_meal > program->philos[i].time_to_die)
            {
                pthread_mutex_lock(&program->dead_lock);
                *program->philos[i].dead = 1;
                pthread_mutex_unlock(&program->dead_lock);
                pthread_mutex_lock(&program->write_lock);
                printf("%zu Philosopher %d has died\n", current_time - program->philos[i].start_time, program->philos[i].id);
                pthread_mutex_unlock(&program->write_lock);
                pthread_mutex_unlock(&program->meal_lock);
                return NULL;
            }
            if (program->philos[i].num_times_to_eat != -1 &&
                program->philos[i].meals_eaten < program->philos[i].num_times_to_eat)
            {
                all_philosophers_ate_enough = 0;
            }
            pthread_mutex_unlock(&program->meal_lock);
        }
        if (program->philos[0].num_times_to_eat != -1 && all_philosophers_ate_enough)
        {
            pthread_mutex_lock(&program->write_lock);
            printf("All philosophers have eaten enough\n");
            pthread_mutex_unlock(&program->write_lock);

            pthread_mutex_lock(&program->dead_lock);
            *program->philos[0].dead = 1;
            pthread_mutex_unlock(&program->dead_lock);
            return NULL;
        }
        usleep(1000);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    t_program *program;
    pthread_t monitor_thread;

    program = NULL;
    if (check_arguments(argc, argv) != 0)
        return (1);
    inititate_program(&program, ft_atoi(argv[1]));
     if (!program)
        return (1);
    initialize_philos(argv, program, argc);
    create_philo_threads(program);
    pthread_create(&monitor_thread, NULL, monitor, program);
    pthread_join(monitor_thread, NULL);
    join_philo_threads(program);
    return (0);
}