#include "header.h"

int e_function_failed(t_philo *data, int flag)
{
    int value;

    w_sem_wait(data->e_function_lock, data, 0);
    if (flag == 1)
        data->e_function_failed = 1;
    value = data->e_function_failed;
    w_sem_post(data->e_function_lock, data, 0);
    return (value);
}

int thread_exited(t_philo *data, int flag)
{
    int value;

    w_sem_wait(data->t_exited_lock, data, 0);
    if (flag == 1)
        data->thread_exited = 1;
    value = data->thread_exited;
    w_sem_post(data->t_exited_lock, data, 0);
    return (value);
}

int philo_died(t_philo *data, int flag)
{
    int value;

    w_sem_wait(data->philo_died_lock, data, 0);
    if (flag == 1)
        data->philo_died = 1;
    value = data->philo_died;
    w_sem_post(data->philo_died_lock, data, 0);
    return (value);
}