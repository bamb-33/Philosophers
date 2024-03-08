/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:38:24 by naadou            #+#    #+#             */
/*   Updated: 2024/03/08 15:44:50 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <sys/time.h>

void	wait_for_p(t_philo *data, pid_t *pids)
{
	int i;

	i = 0;
	while (i < data->philos_num)
		waitpid(pids[i++], 0, 0);
}

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

int	create_processes(t_philo *data, pid_t *pids, pid_t starving_time_id)
{
	struct timeval tv;
	int	i;
	int j;

	i = 0;
	j = 0;
	if (gettimeofday(&(data->time_start), NULL))
	{
		ft_lstclear(&(data->head));
		exit (1);
	}
	while (i < data->philos_num)
	{
		pids[i] = fork();
		printf("%ld\n", get_current_time(&(data->time_start)));
		if (pids[i] == 0)
		{
			// philos_life(data, i);
			exit(0);
		}
		i++;
	}
	// while (i < data->philos_num)
	// {
		//if (!pids[j])
		//{
		//}
	// 	i++;
	// }
	// simulation_started(data);
	// starving_time_id = fork();
	// if (!starving_time_id)
	// 	meals_time(data);
	//function to wait for all processes.
	wait_for_p(data, pids);
	sem_unlink("/lock");
	sem_unlink("/sem");
	sem_close(data->forks);
	sem_close(data->lock);
	return (0);
}
