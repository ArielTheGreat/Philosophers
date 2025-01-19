
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

void *print_helloworld()
{
    printf("HOLAAAA  MUNDITO!");
    return (NULL);
}

int main(int argc, char **argv)
{
    if (!check_arguments(argc, argv))
        return (1);
    
    t_philo philo1;
    t_philo philo2;

    pthread_create(&philo1.thread, NULL, print_helloworld,NULL);
    pthread_create(&philo2.thread, NULL, print_helloworld,NULL);

    return (0);
}