/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/03/07 12:24:31 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(void *args)
{
	t_philo		*data;
	long int	current_time;
	long int	p_s_time_time;
	int			i;

	data = (t_philo *) args;
	i = 0;
	while (all_threads_exited(data, 0) == 0 && gtod_failed_lock(data, 0) == 0)
	{
		current_time = get_current_time(&(data->time_start));
		pthread_mutex_lock(&(data->s_time_lock[i]));
		p_s_time_time = get_current_time(&(data->philos_starving_time[i]));
		pthread_mutex_unlock(&(data->s_time_lock[i]));
		if (current_time == -1 || p_s_time_time == -1)
		{
			gtod_failed_lock(data, 1);
			printf("gettimeofday failed\n");
			break ;
		}
		if (p_s_time_time > data->time_to_die && thread_exited(data, i, 0) == 0)
		{
			philo_died(data, 1);//write
			usleep(500);
			printf("%ld %d  died\n", current_time, i + 1);
			break ;
		}
		i++;
		if (i == data->philos_num)
			i = 0;
	}
}
