/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:38:24 by naadou            #+#    #+#             */
/*   Updated: 2024/03/08 18:10:01 by naadou           ###   ########.fr       */
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
		if (pids[i] == 0)
		{
			philos_life(data, i);
			exit(0);
		}
		i++;
	}
	wait_for_p(data, pids);
	sem_unlink("/lock");
	sem_unlink("/sem");
	sem_close(data->forks);
	sem_close(data->lock);
	return (0);
}
