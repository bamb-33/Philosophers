/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:35 by naadou            #+#    #+#             */
/*   Updated: 2024/02/20 17:26:41 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philos_life(void *args)
{
	t_philo			*data;
	t_forks			*current_node;
	t_forks			*next_node;

	data = (t_philo *) args;
	pthread_mutex_lock(&(data->forks->content));
	next_node = data->forks->next;
	pthread_mutex_lock(&(data->forks->content));
	printf("i am philosopher number %d is now eating\n", data->forks->num);
	usleep(data->time_to_eat);
	printf("i am philosopher number %d is now sleeping\n", data->forks->num);
	usleep(data->time_to_sleep);
	printf("i am philosopher number %d is now thinkin\n", data->forks->num);
	current_node = data->forks;
	data->forks = data->forks->next;
	pthread_mutex_unlock(&(current_node->content));
	philos_life()
}