#include "header.h"

void f(void *arg)
{
    int i;
    int j = 0;;
    t_philo *data = (t_philo *) arg;

    pthread_mutex_lock(&(data->lock));
    i = data->counter++;
    pthread_mutex_unlock(&(data->lock));
    while (j < 2)
    {
        // while (data->hash_table[(i + 1) % 4] == 0);
        if (i % 2 == 0)
        {
            pthread_mutex_lock(&(data->forks[(i + 1) % 4]));
            printf("philo num %d took a fork\n", i + 1);
            pthread_mutex_lock(&(data->forks[i]));
            printf("philo num %d took a fork\n", i + 1);
        }
        else
        {
            pthread_mutex_lock(&(data->forks[i]));
            printf("philo num %d took a fork\n", i + 1);
            pthread_mutex_lock(&(data->forks[(i + 1) % 4]));
            printf("philo num %d took a fork\n", i + 1);
        }
        // data->hash_table[i] = 1;
        printf("philo num %d ate ATE\n", i + 1);
        usleep(200 * 1000);
        pthread_mutex_unlock(&(data->forks[i]));
        pthread_mutex_unlock(&(data->forks[(i + 1) % 4]));
        usleep(200 * 1000);
        j++;
    }
}

int main()
{
    t_philo *data;

    data = (t_philo *) malloc (sizeof(t_philo));
    data->ids = (pthread_t *) malloc (4 * sizeof(pthread_t));
    data->forks = (pthread_mutex_t *) malloc (4 * sizeof(pthread_mutex_t));
    data->hash_table = (int *) malloc (sizeof(int) * 4);
    data->counter = 0;
    for (int i = 0; i < 4; i++)
        pthread_mutex_init(&(data->forks[i]), NULL);
    pthread_mutex_init(&(data->lock), NULL);
    for (int i = 0; i < 4; i++)
    {
        if (i % 2 == 0)
            data->hash_table[i] = 0;
        else
            data->hash_table[i] = 1;
    }
    for (int i = 0; i < 4; i++)
        pthread_create(&(data->ids[i]), NULL, (void *)f, data);
    int i = 4;
    while (i)
	{
		if (pthread_join(data->ids[--i], NULL))
			return (1);
	}
}