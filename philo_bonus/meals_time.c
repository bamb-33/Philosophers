/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/02/24 20:51:55 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(void *args)
{
	t_philo		*data;
	long int	current_time;
	int			i;

	data = (t_philo *) args;
	i = 0;
	while (!data->all_threads_exited)
	{
		current_time = get_current_time(&(data->time_start));
		if (current_time == -1)
		{
			data->philo_died = 1;
			break ;
		}
		if (current_time > data->time_to_die && !data->thread_exited[i])
		{
			data->philo_died = 1;
			printf("%ld %d  died\n", current_time, i + 1);
			break ;
		}
		i++;
		if (i == data->philos_num)
			i = 0;
	}
}