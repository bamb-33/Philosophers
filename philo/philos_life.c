/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/02/22 20:14:11 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// size_t	get_current_time_v2(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

// int	ft_usleep(size_t milliseconds)
// {
// 	size_t	start;

// 	start = get_current_time_v2();
// 	while ((get_current_time_v2() - start) < milliseconds)
// 		usleep(500);
// 	return (0);
// }

void	permission_to_wait_for_fork(t_philo *data, int i)
{
	data->hash_table[i] = 0;
	data->hash_table[(i + 1) % data->philos_num] = 1;
}

int	philosopher_status_printer(t_philo *data, int flag, int i)
{
	if (flag == 5)
		printf("%ld %d  died\n", get_current_time(data->time_start), i + 1);
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
	return (0);
}

void	limited_simulation(t_philo *data, int i)
{
	int	j;

	j = 0;
	while (j < data->num_of_times_philos_must_eat)
	{
		while (data->hash_table[i] == 0);
		pthread_mutex_lock(&(data->forks[i]));
		philosopher_status_printer(data, 1, i);
		// while (data->hash_table[(i + 1) % data->philos_num] == 1);
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
		philosopher_status_printer(data, 4, i);
		if (data->philo_died == 1)
			break ;
		j++;
	}
}

void	infinite_simulation(t_philo *data, int i)
{
	while (1)
	{
		while (data->hash_table[i] == 0);
		pthread_mutex_lock(&(data->forks[i]));
		philosopher_status_printer(data, 1, i);
		// while (data->hash_table[(i + 1) % data->philos_num] == 1);
		pthread_mutex_lock(&(data->forks[(i + 1) % data->philos_num]));
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		// gettimeofday(&(data->philos_starving_time[i]), NULL); //try to minimize the functions in between the mutexes because its slows down the process do it another way
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
		permission_to_wait_for_fork(data, i);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		philosopher_status_printer(data, 4, i);
		if (data->philo_died == 1)
			break ;
	}
}

void	philos_life(void *args)
{
	int		i;
	int		j;
	t_philo	*data;

	data = (t_philo *) args;
	pthread_mutex_lock(&(data->lock));
	i = data->counter;
	gettimeofday(&(data->philos_starving_time[i]), NULL);
	j = 0;
	data->counter++;
	data->simulation_started[i] = 1;
	data->thread_exited[i] = 0;
	pthread_mutex_unlock(&(data->lock));
	if (data->av[5] == NULL)
		infinite_simulation(data, i);
	else
		limited_simulation(data, i);
	data->thread_exited[i] = 1;
}
