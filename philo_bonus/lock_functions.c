/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:58 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 21:12:50 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	e_function_failed(t_philo *data, int flag)
{
	int	value;

	w_sem_wait(data->e_function_lock, data, 0);
	if (flag == 1)
		data->e_function_failed = 1;
	value = data->e_function_failed;
	w_sem_post(data->e_function_lock, data, 0);
	return (value);
}

int	thread_exited(t_philo *data, int flag)
{
	int	value;

	sem_wait(data->t_exited_lock);
	if (flag == 1)
		data->thread_exited = 1;
	value = data->thread_exited;
	w_sem_post(data->t_exited_lock, data, 0);
	return (value);
}

int	philo_died(t_philo *data, int flag)
{
	int	value;

	w_sem_wait(data->philo_died_lock, data, 0);
	if (flag == 1)
		data->philo_died = 1;
	value = data->philo_died;
	w_sem_post(data->philo_died_lock, data, 0);
	return (value);
}

int	dont_print(t_philo *data, int flag)
{
	int	value;

	w_sem_wait(data->dont_print_lock, data, 0);
	if (flag == 1)
		data->dont_print = 1;
	if (flag == 2)
		data->dont_print = 0;
	value = data->dont_print;
	w_sem_post(data->dont_print_lock, data, 0);
	return (value);
}
