/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/02/21 19:02:06 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(void *args)
{
	t_philo	*data;
	int		i;

	data = (t_philo *) args;
	i = 0;
	while (!data->all_threads_exited)
	{
		if (get_current_time(&(data->philos_starving_time[i])) > data->time_to_die)
		{
			printf("%ld\n", get_current_time(&(data->philos_starving_time[i])));
			break ;
		}
		i++;
		if (i == data->philos_num)
			i = 0;
	}
}