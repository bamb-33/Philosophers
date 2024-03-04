/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:38:24 by naadou            #+#    #+#             */
/*   Updated: 2024/03/04 17:32:19 by naadou           ###   ########.fr       */
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

int	waiting_for_threads(t_philo *data, pthread_t *ids, pthread_t s_id, int i)
{
	while (i)
	{
		if (pthread_join(ids[--i], NULL))
			return (1);
	}
	data->all_threads_exited = 1;
	if (pthread_join(s_id, NULL))
		return (1);
	return (0);
}

int	create_processes(t_philo *data,pid_t *pids, pid_t starving_time_id)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		pids[i] = fork();
		if (!pids[i])
		{
			philos_life(data, i);
			exit(0);//doing this instead of the if else statment
		}
		i++;
	}
	// simulation_started(data);
	starving_time_id = fork();
	if (!starving_time_id)
		meals_time(data);
	//function to wait for all processes.
	return (0);
}
