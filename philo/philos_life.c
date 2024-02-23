/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/02/23 18:46:14 by naadou           ###   ########.fr       */
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

// void	permission_to_wait_for_fork(t_philo *data, int i)
// {
// 	data->hash_table[i] = 0;
// 	data->hash_table[(i + 1) % data->philos_num] = 1;
// }

// void	permission_to_wait_for_fork(t_philo *data, int i)
// {
// 	data->hash_table[i] = 0;
// 	data->hash_table[(i + 1) % data->philos_num] = 1;
// }

void	philosopher_status_printer(t_philo *data, int flag, int i)
{
	if (data->philo_died == 1)
		return ;
	if (flag == 1)
		printf("%ld %d  has taken a fork\n", get_current_time(data->time_start), i + 1);
	else if (flag == 2)
		printf("%ld %d  is eating\n", get_current_time(data->time_start), i + 1);
	else if (flag == 3)
		printf("%ld %d  is sleeping\n", get_current_time(data->time_start), i + 1);
	else if (flag == 4)
		printf("%ld %d  is thinking\n", get_current_time(data->time_start), i + 1);
}

void	limited_simulation(t_philo *data, int i)
{
	int	j;

	j = 0;
	while (j < data->num_of_times_philos_must_eat)
	{
		while (data->hash_table[(i + 1) % data->philos_num] == 1);
		pthread_mutex_lock(&(data->forks[(i + 1) % data->philos_num]));
		philosopher_status_printer(data, 1, i);
		pthread_mutex_lock(&(data->forks[i]));
		gettimeofday(&(data->philos_starving_time[i]), NULL);
		data->hash_table[i] = 0;
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
		philosopher_status_printer(data, 3, i);
		philosopher_status_printer(data, 4, i);
		usleep(data->time_to_sleep);
		if (data->philo_died == 1)
			break ;
		j++;
	}
}

void	infinite_simulation(t_philo *data, int i)
{
	char	str;

	str = 0;
	while (1)
	{
		while (data->hash_table[(i + 1) % data->philos_num] == 1);
		pthread_mutex_lock(&(data->forks[(i + 1) % data->philos_num]));
		philosopher_status_printer(data, 1, i);
		pthread_mutex_lock(&(data->forks[i]));
		gettimeofday(&(data->philos_starving_time[i]), NULL);
		data->hash_table[i] = 0;
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
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
	t_philo	*data;

	data = (t_philo *) args;
	pthread_mutex_lock(&(data->lock));
	i = data->counter++;
	gettimeofday(&(data->philos_starving_time[i]), NULL);
	data->simulation_started[i] = 1;
	philosopher_status_printer(data, 4, i);
	pthread_mutex_unlock(&(data->lock));
	if (data->av[5] == NULL)
		infinite_simulation(data, i);
	else
		limited_simulation(data, i);
	data->thread_exited[i] = 1;
}
