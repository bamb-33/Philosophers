/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/03/09 18:51:39 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(t_philo *data)
{
	while (!data->thread_exited)
	{
		sem_wait(data->lock);
		if (get_current_time(&(data->philos_starving_time), data) > data->time_to_die)
		{
			data->philo_died = 1;
			usleep(500);
			printf("%ld %d  died\n", get_current_time(&(data->time_start), data), data->philos_index + 1);
			sem_unlink("/sem_lock");
			sem_close(data->lock);
			exit(1);
		}
		sem_post(data->lock);
	}
}
