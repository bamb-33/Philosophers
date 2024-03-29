/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/03/19 20:08:39 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(t_philo *data)
{
	while (!thread_exited(data, 0) && !e_function_failed(data, 0))
	{
		if (get_current_time(&(data->philos_starving_time), data)
			> data->time_to_die)
		{
			philo_died(data, 1);
			w_sem_wait(data->stop_lock, data, 0); 
			printf("%ld %d died\n", get_current_time(&(data->time_start), data),
				data->philos_index + 1);
			break ;
		}
	}
}
