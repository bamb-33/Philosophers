/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:38:24 by naadou            #+#    #+#             */
/*   Updated: 2024/03/19 02:12:22 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	wait_for_p(t_philo *data, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
		waitpid(pids[i++], 0, 0);
}

void	unlink_sems(t_philo *data)
{
	w_sem_unlink("/sem", data, 1);
	w_sem_unlink("/sem_gtod_lock", data, 1);
	w_sem_unlink("/sem_t_exited_lock", data, 1);
	w_sem_unlink("/sem_e_function_lock", data, 1);
	w_sem_unlink("/sem_philo_died_lock", data, 1);
	w_sem_unlink("/sem_test_lock", data, 1);
}

void	create_processes(t_philo *data, pid_t *pids)
{
	int				i;

	i = 0;
	w_gettimeofday_1(&(data->time_start), NULL, data);
	w_gettimeofday_1(&(data->philos_starving_time), NULL, data);
	while (i < data->philos_num)
	{
		pids[i] = w_fork(data, i);
		if (pids[i] == 0)
			philos_life(data, i);
		usleep(50);
		i++;
	}
	wait_for_p(data, pids);
	unlink_sems(data);
	w_sem_close(data->forks, data, 1);
	w_sem_close(data->test_lock, data, 1);
}
