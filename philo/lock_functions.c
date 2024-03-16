/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:32:39 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 21:18:56 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	counter(t_philo *data)
{
	int	value;

	pthread_mutex_lock(&(data->counter_lock));
	value = data->counter++;
	pthread_mutex_unlock(&(data->counter_lock));
	return (value);
}

int	simulation_started(t_philo *data, int i, int flag)
{
	int	value;

	pthread_mutex_lock(&(data->s_started_lock[i]));
	if (flag == 1)
		data->simulation_started[i] = 1;
	value = data->simulation_started[i];
	pthread_mutex_unlock(&(data->s_started_lock[i]));
	return (value);
}

int	hash_table(t_philo *data, int i, int flag)
{
	int	value;

	pthread_mutex_lock(&(data->h_table_lock[i]));
	if (flag == 1)
		data->hash_table[i] = 1;
	value = data->hash_table[i];
	pthread_mutex_unlock(&(data->h_table_lock[i]));
	return (value);
}

int	philo_died(t_philo *data, int flag)
{
	int	value;

	pthread_mutex_lock(&(data->philo_died_lock));
	if (flag == 1)
		data->philo_died = 1;
	value = data->philo_died;
	pthread_mutex_unlock(&(data->philo_died_lock));
	return (value);
}

int	thread_exited(t_philo *data, int i, int flag)
{
	int	value;

	pthread_mutex_lock(&(data->thread_exited_lock[i]));
	if (flag == 1)
		data->thread_exited[i] = 1;
	value = data->thread_exited[i];
	pthread_mutex_unlock(&(data->thread_exited_lock[i]));
	return (value);
}
