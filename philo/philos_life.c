/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/02/20 20:38:31 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philos_life(void *args)
{
	int		i;
	t_philo	*data;

	data = (t_philo *) args;
	pthread_mutex_lock(&(data->lock));
	i = data->counter;
	data->counter++;
	pthread_mutex_unlock(&(data->lock));

	// pthread_mutex_lock(&(data->forks[i]));
	// pthread_mutex_lock(&(next_node[i]));
	printf("i am philosopher number %d is now eating\n", i);
	usleep(data->time_to_eat);
	printf("i am philosopher number %d is now sleeping\n", i);
	usleep(data->time_to_sleep);
	printf("i am philosopher number %d is now thinkin\n", i);
	// pthread_mutex_unlock(&(next_node[i]));
	// pthread_mutex_unlock(&(current_node[i]));
}