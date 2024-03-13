#include "header.h"

int gtod_failed(t_philo *data, int flag)
{
    int value;

    sem_wait(data->gtod_lockv2);
    if (flag == 1)
        data->gtod_failed = 1;
    value = data->gtod_failed;
    sem_post(data->gtod_lockv2);
    return (value);
}

int thread_exited(t_philo *data, int flag)
{
    int value;

    sem_wait(data->t_exited_lock);
    if (flag == 1)
        data->thread_exited = 1;
    value = data->thread_exited;
    sem_post(data->t_exited_lock);
    return (value);
}

int philo_died(t_philo *data, int flag)
{
    int value;

    sem_wait(data->philo_died_lock);
    if (flag == 1)
        data->philo_died = 1;
    value = data->philo_died;
    sem_post(data->philo_died_lock);
    return (value);
}