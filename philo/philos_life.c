/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 21:16:08 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philosopher_status_printer(t_philo *data, int flag, int i)
{
	long int	current_time;

	current_time = get_current_time(&(data->time_start));
	if (current_time == -1)
	{
		gtod_failed_lock(data, 1);
		return ;
	}
	if (philo_died(data, 0) || gtod_failed_lock(data, 0))
		return ;
	if (flag == 1)
		printf("%ld %d  has taken a fork\n", current_time, i + 1);
	else if (flag == 2)
		printf("%ld %d  is eating\n", current_time, i + 1);
	else if (flag == 3)
		printf("%ld %d  is sleeping\n", current_time, i + 1);
	else if (flag == 4)
		printf("%ld %d  is thinking\n", current_time, i + 1);
}

void	philo_sync(int i, t_philo *data)
{
	int	z;

	z = (i + 1) % data->philos_num;
	if (hash_table(data, z, 0) == 1 && data->philos_num % 2 == 1)
		usleep(data->time_to_eat);
	while (hash_table(data, z, 0) == 0 && data->philos_num % 2 == 0)
	{
		hash_table(data, z, 1);
		usleep(0);
	}
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&(data->forks[z]));
		philosopher_status_printer(data, 1, i);
		pthread_mutex_lock(&(data->forks[i]));
	}
	else
	{
		pthread_mutex_lock(&(data->forks[i]));
		philosopher_status_printer(data, 1, i);
		pthread_mutex_lock(&(data->forks[z]));
	}
}

void	limited_simulation(t_philo *data, int i)
{
	int	j;

	j = 0;
	while (j++ < data->num_of_times_philos_must_eat)
	{
		philosopher_status_printer(data, 4, i);
		philo_sync(i, data);
		pthread_mutex_lock(&(data->s_time_lock[i]));
		gettimeofday(&(data->philos_starving_time[i]), NULL);
		pthread_mutex_unlock(&(data->s_time_lock[i]));
		hash_table(data, i, 1);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
		pthread_mutex_unlock(&(data->forks[i]));
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (philo_died(data, 0) || gtod_failed_lock(data, 0))
			break ;
	}
}

void	infinite_simulation(t_philo *data, int i)
{
	while (1)
	{
		philosopher_status_printer(data, 4, i);
		philo_sync(i, data);
		pthread_mutex_lock(&(data->s_time_lock[i]));
		gettimeofday(&(data->philos_starving_time[i]), NULL);
		pthread_mutex_unlock(&(data->s_time_lock[i]));
		hash_table(data, i, 1);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
		pthread_mutex_unlock(&(data->forks[i]));
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (philo_died(data, 0) || gtod_failed_lock(data, 0))
			break ;
	}
}

void	philos_life(void *args)
{
	int		i;
	t_philo	*data;

	data = (t_philo *) args;
	i = counter(data);
	if (gettimeofday(&(data->philos_starving_time[i]), NULL))
	{
		gtod_failed_lock(data, 1);
		printf("gettimeofday failed\n");
		return ;
	}
	simulation_started(data, i, 1);
	if (data->philos_num == 1)
	{
		philosopher_status_printer(data, 4, i);
		while (philo_died(data, 0) == 0)
			usleep(1);
	}
	else if (data->av[5] == NULL)
		infinite_simulation(data, i);
	else
		limited_simulation(data, i);
	thread_exited(data, i, 1);
}
