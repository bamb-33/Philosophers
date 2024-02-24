/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:38:24 by naadou            #+#    #+#             */
/*   Updated: 2024/02/24 12:38:51 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	simulation_started(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (data->simulation_started[i])
			i++;
	}
}

int	create_threads(t_philo *data, pthread_t *ids, pthread_t starving_time_id)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_create(&(ids[i++]), NULL, (void *) philos_life, data))
			return (1);
	}
	simulation_started(data);
	if (pthread_create(&starving_time_id, NULL, (void *) meals_time, data))
		return (1);
	while (i)
		pthread_join(ids[--i], NULL);
	data->all_threads_exited = 1;
	pthread_join(starving_time_id, NULL);
	return (0);
}
