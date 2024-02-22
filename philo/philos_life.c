/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/02/22 10:17:04 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	philosopher_status_printer(t_philo *data, int flag, int i)
{
	if (data->philo_died == 1)
		return (1);
	if (flag == 1)
		printf("%ld %d  has taken a fork\n", get_current_time(data->time_start), i + 1);
	else if (flag == 2)
		printf("%ld %d  is eating\n", get_current_time(data->time_start), i + 1);
	else if (flag == 3)
		printf("%ld %d  is sleeping\n", get_current_time(data->time_start), i + 1);
	else if (flag == 4)
		printf("%ld %d  is thinking\n", get_current_time(data->time_start), i + 1);
	else if (flag == 5)
		printf("%ld %d  died\n", get_current_time(data->time_start), i + 1);
	return (0);
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
		while (data->hash_table[i] == 0);
		pthread_mutex_lock(&(data->forks[i]));
		philosopher_status_printer(data, 1, i);
		pthread_mutex_lock(&(data->forks[(i + 1) % data->philos_num]));
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		gettimeofday(&(data->philos_starving_time[i]), NULL);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
		permission_to_wait_for_fork(data, i);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (philosopher_status_printer(data, 4, i) == 1)
			return ;
		//bug to fix: when the number of time to eat for a thread is reached the starving cycle for that thread should stop
		j++;
	}
}