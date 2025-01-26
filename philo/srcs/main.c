
#include "../philo.h"

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

int main(int argc, char **argv)
{
    t_program *program;
    int i;

    program = NULL;
    if (check_arguments(argc, argv) != 0)
        return (1);
    inititate_program(&program, ft_atoi(argv[1]));
     if (!program)
        return (1);
    initialize_philos(argv, program, argc);
    i= 0;
    while(i < ft_atoi(argv[1]))
    {
        printf("%i\n", program->philos[i].id);
        i++;
    }
    return (0);
}