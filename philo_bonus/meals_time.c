/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/03/11 21:23:10 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(t_philo *data)
{
	while (!thread_exited(data, 0) && !e_function_failed(data, 0))
	{
		if (get_current_time(&(data->philos_starving_time), data)//writing
			> data->time_to_die)
		{
			philo_died(data, 1);
			printf("%ld %d died\n", get_current_time(&(data->time_start), data),
				data->philos_index + 1);//writing
			break;
		}
	}
}
