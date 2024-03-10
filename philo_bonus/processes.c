/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:38:24 by naadou            #+#    #+#             */
/*   Updated: 2024/03/09 18:44:14 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void exit_status(t_philo *data)
{
	int status;
	int i;

	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 1)
	{
		while (i < data->philos_num)
			kill(data->pids[i++], SIGTERM);
	}
}

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

	i = 0;
	w_gettimeofday(&(data->time_start), NULL, data->head);
	w_gettimeofday(&(data->philos_starving_time), NULL, data->head);
	while (i < data->philos_num)
	{
		pids[i] = w_fork(data, i);
		if (pids[i] == 0)
		{
			philos_life(data, i);
			ft_lstclear(&(data->head));
			exit(0);
		}
		usleep(50);
		i++;
	}
	exit_status(data);
	wait_for_p(data, pids);
	sem_unlink("/sem");
	sem_close(data->forks);
	return (0);
}
