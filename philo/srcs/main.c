
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

void create_philos(int number_philo, t_program program)
{
    int i;
    t_philo *philo;

    i = 0;
    while(i < number_philo)
    {
        philo = (t_philo*)malloc(sizeof(t_philo));
        philo->id = i+1;
        program.philos[i] = *philo;
        i++;
    }
}

int main(int argc, char **argv)
{
    t_program *program;    

    program = (t_program*)malloc(sizeof(t_program));
    if (check_arguments(argc, argv) != 0)
        return (1);
    create_philos(ft_atoi(argv[1]), *program);
    int i= 0;
    while(i < ft_atoi(argv[1]))
    {
        printf("%i\n", (*program).philos[i].id);
        i++;
    }
    return (0);
}