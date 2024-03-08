/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/03/08 18:21:42 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philosopher_status_printer(t_philo *data, int flag, int i)
{
	if (flag == 1)
		printf("%ld %d  has taken a fork\n",
			get_current_time(&(data->time_start)), i + 1);
	else if (flag == 2)
		printf("%ld %d  is eating\n",
			get_current_time(&(data->time_start)), i + 1);
	else if (flag == 3)
		printf("%ld %d  is sleeping\n",
			get_current_time(&(data->time_start)), i + 1);
	else if (flag == 4)
		printf("%ld %d  is thinking\n",
			get_current_time(&(data->time_start)), i + 1);
}

// void	limited_simulation(t_philo *data, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (j < data->num_of_times_philos_must_eat)
// 	{
// 		while (data->hash_table[(i + 1) % data->philos_num] == 1)
// 			usleep(0);
// 		pthread_mutex_lock(&(data->forks[(i + 1) % data->philos_num]));
// 		philosopher_status_printer(data, 1, i);
// 		pthread_mutex_lock(&(data->forks[i]));
// 		gettimeofday(&(data->philos_starving_time[i]), NULL);
// 		data->hash_table[i] = 0;
// 		philosopher_status_printer(data, 1, i);
// 		philosopher_status_printer(data, 2, i);
// 		usleep(data->time_to_eat);
// 		pthread_mutex_unlock(&(data->forks[i]));
// 		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
// 		philosopher_status_printer(data, 3, i);
// 		usleep(data->time_to_sleep);
// 		philosopher_status_printer(data, 4, i);
// 		if (data->philo_died == 1)
// 			break ;
// 		j++;
// 	}
// }

void	infinite_simulation(t_philo *data, int i, int controler)
{
	int j;

	j = 0;
	while (j < 3)
	{
		philosopher_status_printer(data, 4, i);
		sem_wait(data->forks);
		philosopher_status_printer(data, 1, i);
		sem_wait(data->forks);
		gettimeofday(&(data->philos_starving_time), NULL);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		j++;
	}
}

void	philos_life(t_philo *data, int i)
{
	gettimeofday(&(data->philos_starving_time), NULL);
	data->philos_index = i;
	// if (data->philos_num == 1)
	// {
	// 	philosopher_status_printer(data, 4, i);
	// 	while (data->philo_died == 0)
	// 		usleep(1);
	// }
	// else if (data->av[5] == NULL)
	infinite_simulation(data, i, i);
	// else
	// 	limited_simulation(data, i, i);
	data->thread_exited = 1;
}
