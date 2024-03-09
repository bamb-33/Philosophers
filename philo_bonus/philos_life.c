/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/03/09 18:34:37 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philosopher_status_printer(t_philo *data, int flag, int i)
{
	if (data->philo_died == 1)
		return ;
	if (flag == 1)
		printf("%ld %d  has taken a fork\n",
			get_current_time(&(data->time_start), data), i + 1);
	else if (flag == 2)
		printf("%ld %d  is eating\n",
			get_current_time(&(data->time_start), data), i + 1);
	else if (flag == 3)
		printf("%ld %d  is sleeping\n",
			get_current_time(&(data->time_start), data), i + 1);
	else if (flag == 4)
		printf("%ld %d  is thinking\n",
			get_current_time(&(data->time_start), data), i + 1);
}

void	limited_simulation(t_philo *data, int i)
{
	int	j;

	j = 0;
	pthread_create(&(data->t_id), NULL, (void *) meals_time, data);
	while (j < data->num_of_times_philos_must_eat)
	{
		philosopher_status_printer(data, 4, i);
		sem_wait(data->forks);
		philosopher_status_printer(data, 1, i);
		sem_wait(data->forks);
		w_gettimeofday(&(data->philos_starving_time), NULL, data->head);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (data->philo_died == 1)
			break ;
		j++;
	}
}

void	infinite_simulation(t_philo *data, int i)
{
	pthread_create(&(data->t_id), NULL, (void *) meals_time, data);
	while (1)
	{
		philosopher_status_printer(data, 4, i);
		sem_wait(data->forks);
		philosopher_status_printer(data, 1, i);
		sem_wait(data->forks);
		w_gettimeofday(&(data->philos_starving_time), NULL, data->head);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (data->philo_died == 1)
			break ;
	}
}

void	philos_life(t_philo *data, int i)
{
	data->philos_index = i;
	if (data->philos_num == 1)
	{
		philosopher_status_printer(data, 4, i);
		usleep(data->time_to_die * 1000);
		printf("%ld %d  died\n", get_current_time(&(data->time_start), data), i + 1);
		exit(0);
	}
	else if (data->av[5] == NULL)
		infinite_simulation(data, i);
	else
		limited_simulation(data, i);
	data->thread_exited = 1;
	pthread_join(data->t_id, NULL);
	if (data->philo_died == 1)
	{
		exit(1);
	}
	exit(0);
}
