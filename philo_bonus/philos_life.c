/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 20:26:28 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	opening_closing_sems(t_philo *data, int flag)
{
	if (flag == 0)
	{
		data->gtod_lock = w_sem_open("/sem_gtod_lock", 1, data, 0);
		data->e_function_lock = w_sem_open("/sem_e_function_lock", 1, data, 0);
		data->t_exited_lock = w_sem_open("/sem_t_exited_lock", 1, data, 0);
		data->philo_died_lock = w_sem_open("/sem_philo_died_lock", 1, data, 0);
	}
	else
	{
		w_sem_close(data->forks, data, 0);
		w_sem_close(data->gtod_lock, data, 0);
		w_sem_close(data->e_function_lock, data, 0);
		w_sem_close(data->t_exited_lock, data, 0);
		w_sem_close(data->philo_died_lock, data, 0);
		ft_lstclear((data->head));
	}
}

void	philosopher_status_printer(t_philo *data, int flag, int i)
{
	if (philo_died(data, 0) || e_function_failed(data, 0))
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
		w_sem_wait(data->forks, data, 0);
		philosopher_status_printer(data, 1, i);
		w_sem_wait(data->forks, data, 0);
		w_gettimeofday(&(data->philos_starving_time), NULL, data);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		w_sem_post(data->forks, data, 0);
		w_sem_post(data->forks, data, 0);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (philo_died(data, 0) || e_function_failed(data, 0))
			break ;
		j++;
	}
	thread_exited(data, 1);
}

void	infinite_simulation(t_philo *data, int i, int controler)
{
	while (1)
	{
		philosopher_status_printer(data, 4, i);
		if (controler == 0 && data->philos_num % 2 == 1)
			usleep(data->time_to_eat);
		controler = 0;
		w_sem_wait(data->forks, data, 0);
		philosopher_status_printer(data, 1, i);
		w_sem_wait(data->forks, data, 0);
		w_gettimeofday(&(data->philos_starving_time), NULL, data);
		philosopher_status_printer(data, 1, i);
		philosopher_status_printer(data, 2, i);
		usleep(data->time_to_eat);
		w_sem_post(data->forks, data, 0);
		w_sem_post(data->forks, data, 0);
		philosopher_status_printer(data, 3, i);
		usleep(data->time_to_sleep);
		if (philo_died(data, 0) || e_function_failed(data, 0))
			break ;
	}
	thread_exited(data, 1);
}

void	philos_life(t_philo *data, int i)
{
	int	controler;

	data->philos_index = i;
	if (i < data->philos_num / 2)
		controler = 1;
	else
		controler = 0;
	opening_closing_sems(data, 0);
	pthread_create(&(data->t_id), NULL, (void *) meals_time, data);
	if (data->philos_num == 1)
	{
		philosopher_status_printer(data, 4, i);
		while (!philo_died(data, 0))
			usleep(0);
	}
	else if (data->av[5] == NULL)
		infinite_simulation(data, i, controler);
	else
		limited_simulation(data, i, controler);
	pthread_join(data->t_id, NULL);
	if (philo_died(data, 0) == 1)
	{
		opening_closing_sems(data, 1);
		exit(1);
	}
	opening_closing_sems(data, 1);
	exit(0);
}
