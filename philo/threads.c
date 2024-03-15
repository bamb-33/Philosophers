/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:38:24 by naadou            #+#    #+#             */
/*   Updated: 2024/02/29 12:33:19 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_meals_thread(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (simulation_started(data, i, 0))
			i++;
	}
}

int	waiting_for_threads(t_philo *data, pthread_t *ids, pthread_t s_id, int i)
{
	while (i)
	{
		if (pthread_join(ids[--i], NULL))
			return (1);
	}
	all_threads_exited(data, 1);
	if (pthread_join(s_id, NULL))
		return (1);
	return (0);
}

int	create_threads(t_philo *data, pthread_t *ids, pthread_t starving_time_id)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_create(&(ids[i++]), NULL, (void *) philos_life, data))
		{
			philo_died(data, 1);
			waiting_for_threads(data, ids, starving_time_id, i);
			ft_lstclear((data->head));
			return (1);
		}
	}
	create_meals_thread(data);
	if (pthread_create(&starving_time_id, NULL, (void *) meals_time, data))
	{
		ft_lstclear((data->head));
		return (1);
	}
	if (waiting_for_threads(data, ids, starving_time_id, i))
	{
		ft_lstclear((data->head));
		return (1);
	}
	return (0);
}
