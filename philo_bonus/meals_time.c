/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/03/08 18:21:34 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(t_philo *data)
{
	while (!data->thread_exited)
	{
		if (get_current_time(&(data->philos_starving_time)) > data->time_to_die)
		{
			printf("%ld %d  died\n", get_current_time(&(data->time_start)), data->philos_index + 1);
			exit(0);
		}
	}
}
