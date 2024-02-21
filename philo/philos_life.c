/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/02/21 19:04:15 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long int	get_current_time(struct timeval *time_start)
{
	struct timeval current_time;
	long int	time_in_micro_s;

	if (gettimeofday(&current_time, NULL))
	{
		printf("gettimeofday failed\n");
		exit(1);
	}
	time_in_micro_s = (current_time.tv_sec * 1e6 + current_time.tv_usec) - (time_start->tv_sec * 1e6 + time_start->tv_usec);
	return (time_in_micro_s / 1000);
}

void	permission_to_wait_for_fork(t_philo *data, int i)
{
	if (data->hash_table[i] == 1)
		data->hash_table[i] = 0;
	else
		data->hash_table[i] = 1;
	if (data->hash_table[(i + 1) % data->philos_num] == 1)
		data->hash_table[(i + 1) % data->philos_num] = 0;
	else
		data->hash_table[(i + 1) % data->philos_num] = 1;
}

void	philos_life(void *args)
{
	int		i;
	int		j;
	t_philo	*data;

	data = (t_philo *) args;
	pthread_mutex_lock(&(data->lock));
	i = data->counter;
	j = 0;
	data->counter++;
	if (gettimeofday(&(data->philos_starving_time[i]), NULL))
	{
		printf("gettimeofday failed\n");
		exit(1);
	}
	data->simulation_started[i] = 1;
	pthread_mutex_unlock(&(data->lock));
	while (j < data->num_of_times_philos_must_eat)
	{
		while (data->hash_table[i] == 0)
			usleep(1);
		pthread_mutex_lock(&(data->forks[i]));
		pthread_mutex_lock(&(data->forks[(i + 1) % data->philos_num]));
		gettimeofday(&(data->philos_starving_time[i]), NULL);
		printf("%ld Philosopher number %d is now eating\n", get_current_time(data->time_start), i + 1);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
		permission_to_wait_for_fork(data, i);
		printf("%ld Philosopher number %d is now sleeping\n", get_current_time(data->time_start), i + 1);
		usleep(data->time_to_sleep);
		printf("%ld Philosopher number %d is now thinkin\n", get_current_time(data->time_start), i + 1);
		j++;
	}
}