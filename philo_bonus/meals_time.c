/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:08 by naadou            #+#    #+#             */
/*   Updated: 2024/03/19 20:08:39 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	meals_time(t_philo *data)
{
	while (!thread_exited(data, 0) && !e_function_failed(data, 0))
	{
		w_gettimeofday(&(data->test_time), NULL, data);
		dont_print(data, 1);
		w_sem_wait(data->test_lock, data, 0);
		dont_print(data, 2);
		if ((get_current_time(&(data->test_time), data) * 1000) >= 1000)//big big probleme //cus there's delay in my way of doing things so even a philosopher was supposed to be dead its simulation will keep on going cus the meals_time
        //function is being posed to actually stop the simulation.

		//mybe set a variable that stops the printer from printing while its waiting for the lock
		{
			philo_died(data, 1);
			w_sem_post(data->test_lock, data, 0);
			break ;
		}
		if (get_current_time(&(data->philos_starving_time), data)
			> data->time_to_die)
		{
			philo_died(data, 1);
			usleep(1001);
			w_sem_post(data->test_lock, data, 0);
			usleep(500);
			printf("%ld %d died\n", get_current_time(&(data->time_start), data),
				data->philos_index + 1);
			break ;
		}
		w_sem_post(data->test_lock, data, 0);
	}
}
