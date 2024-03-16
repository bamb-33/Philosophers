/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_functions_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:18:20 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 21:18:35 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	all_threads_exited(t_philo *data, int flag)
{
	int	value;

	pthread_mutex_lock(&(data->a_t_exited_lock));
	if (flag == 1)
		data->all_threads_exited = 1;
	value = data->all_threads_exited;
	pthread_mutex_unlock(&(data->a_t_exited_lock));
	return (value);
}

int	gtod_failed_lock(t_philo *data, int flag)
{
	int	value;

	pthread_mutex_lock(&(data->a_t_exited_lock));
	if (flag == 1)
		data->gtod_failed = 1;
	value = data->gtod_failed;
	pthread_mutex_unlock(&(data->a_t_exited_lock));
	return (value);
}
