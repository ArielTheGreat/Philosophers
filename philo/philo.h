#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>

typedef struct philo
{
    pthread_t   thread;
    int         id;
}   t_philo;

#endif