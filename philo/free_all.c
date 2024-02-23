/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:29:23 by naadou            #+#    #+#             */
/*   Updated: 2024/02/23 11:48:06 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_all(t_philo *data)
{
	free (data->hash_table);
	free (data->simulation_started);
	free (data->ids);
	free (data->thread_exited);
	free (data->philos_starving_time);
	free (data->time_start);
	free (data->forks);
	free (data);
}