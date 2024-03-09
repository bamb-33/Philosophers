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
		if (get_current_time(&(data->philos_starving_time), data) > data->time_to_die)
		{
			printf("%ld %d  died\n", get_current_time(&(data->time_start), data), data->philos_index + 1);
			//use lock when you try to change this to avoid data races i guess
			data->philo_died = 1;
			exit(1);
		}
	}
}
