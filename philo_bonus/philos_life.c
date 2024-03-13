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

void	philosopher_status_printer(t_philo *data, int flag, int i)//writing i guess
{
	if (philo_died(data, 0))
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
		w_gettimeofday(&(data->philos_starving_time), NULL, data);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (philo_died(data, 0))
			break;
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
		w_gettimeofday(&(data->philos_starving_time), NULL, data);//writing
		sem_post(data->lock);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (philo_died(data, 0))
			break;
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
	data->gtod_lock = w_sem_open("/sem_gtod_lock", 1, data->head);
	data->gtod_lockv2 = w_sem_open("/sem_gtod_lockv2", 1, data->head);
	data->t_exited_lock = w_sem_open("/sem_t_exited_lock", 1, data->head);
	data->philo_died_lock = w_sem_open("/sem_philo_died_lock", 1, data->head);
	pthread_create(&(data->t_id), NULL, (void *) meals_time, data);//start of the thread
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
	thread_exited(data, 1);//writing
	pthread_join(data->t_id, NULL);
	sem_unlink("/sem_lock");
	sem_close(data->lock);
	sem_unlink("/sem_gtod_lock");
	sem_close(data->gtod_lock);
	sem_unlink("/sem_gtod_lockv2");
	sem_close(data->gtod_lockv2);
	sem_unlink("/sem_t_thread_lock");
	sem_close(data->t_exited_lock);
	if (philo_died(data, 0) == 1)
	{
		sem_unlink("/sem_philo_died_lock");
		sem_close(data->philo_died_lock);
		ft_lstclear(&(data->head));
		exit(1);
	}
	else
	{
		sem_unlink("/sem_philo_died_lock");
		sem_close(data->philo_died_lock);
		ft_lstclear(&(data->head));
		exit(0);
	}
}
