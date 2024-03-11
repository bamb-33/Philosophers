/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/03/11 11:41:22 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philosopher_status_printer(t_philo *data, int flag, int i)
{
	if (data->philo_died == 1)
		return ;
	if (flag == 1)
		printf("%ld %d has taken a fork\n",
			get_current_time(&(data->time_start), data), i + 1);
	else if (flag == 2)
		printf("%ld %d is eating\n",
			get_current_time(&(data->time_start), data), i + 1);
	else if (flag == 3)
		printf("%ld %d is sleeping\n",
			get_current_time(&(data->time_start), data), i + 1);
	else if (flag == 4)
		printf("%ld %d is thinking\n",
			get_current_time(&(data->time_start), data), i + 1);
}

void	limited_simulation(t_philo *data, int i, int controler)
{
	int	j;

	j = 0;
	while (j < data->num_of_times_philos_must_eat)
	{
		philosopher_status_printer(data, 4, i);
		if (controler == 0 && data->philos_num % 2 == 1)
			usleep(data->time_to_eat);
		controler = 0;
		sem_wait(data->forks);
		philosopher_status_printer(data, 1, i);
		sem_wait(data->forks);
		sem_wait(data->lock);
		w_gettimeofday(&(data->philos_starving_time), NULL, data->head);
		sem_post(data->lock);
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

void	infinite_simulation(t_philo *data, int i, int controler)
{
	while (1)
	{
		philosopher_status_printer(data, 4, i);
		if (controler == 0 && data->philos_num % 2 == 1)
			usleep(data->time_to_eat);
		controler = 0;
		sem_wait(data->forks);
		philosopher_status_printer(data, 1, i);
		sem_wait(data->forks);
		sem_wait(data->lock);
		w_gettimeofday(&(data->philos_starving_time), NULL, data->head);
		sem_post(data->lock);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
	}
}

void	philos_life(t_philo *data, int i)
{
	int	controler;

	data->philos_index = i;
	if (i < data->philos_num / 2)
		controler = 1;
	else
		controler = 0;
	data->lock = w_sem_open("/sem_lock", 1, data->head);
	pthread_create(&(data->t_id), NULL, (void *) meals_time, data);
	if (data->philos_num == 1)
	{
		philosopher_status_printer(data, 4, i);
		while (1)
			usleep(0);
	}
	else if (data->av[5] == NULL)
		infinite_simulation(data, i, controler);
	else
		limited_simulation(data, i, controler);
	data->thread_exited = 1;
	pthread_join(data->t_id, NULL);
	sem_unlink("/sem_lock");
	sem_close(data->lock);
}
