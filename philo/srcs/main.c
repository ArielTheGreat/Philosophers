
#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	z;
	int	p;

	z = 0;
	p = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			p = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		z = z * 10 + (*str - '0');
		str++;
	}
	return (p * z);
}

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
        program->philos[i].start_time = 0;
        program->philos[i].dead = &program->dead_flag;
        program->philos[i].write_lock = &program->write_lock;
        program->philos[i].meal_lock = &program->meal_lock;
        program->philos[i].dead_lock = &program->dead_lock;
        i++;
    }
}

void inititate_program(t_program **program, int number_philos)
{
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
}

int main(int argc, char **argv)
{
    t_program *program;

    program = NULL;
    if (check_arguments(argc, argv) != 0)
        return (1);
    inititate_program(&program, ft_atoi(argv[1]));
    initialize_philos(argv, program, argc);
    int i= 0;
    while(i < ft_atoi(argv[1]))
    {
        printf("%i\n", program->philos[i].id);
        i++;
    }
    return (0);
}