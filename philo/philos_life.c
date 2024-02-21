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
	int		j;
	t_philo	*data;

	data = (t_philo *) args;
	pthread_mutex_lock(&(data->lock));
	i = data->counter;
	j = 0;
	data->counter++;
	pthread_mutex_unlock(&(data->lock));
	while (j < data->num_of_times_philos_must_eat)
	{
		while (data->hash_table[i] == 0)
			usleep(1);
		pthread_mutex_lock(&(data->forks[i]));
		pthread_mutex_lock(&(data->forks[(i + 1) % data->philos_num]));
		printf("i am philosopher number %d is now eating\n", i);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_unlock(&(data->forks[(i + 1) % data->philos_num]));
		if (data->hash_table[i] == 1)
			data->hash_table[i] = 0;
		else
			data->hash_table[i] = 1;
		if (data->hash_table[(i + 1) % data->philos_num] == 1)
			data->hash_table[(i + 1) % data->philos_num] = 0;
		else
			data->hash_table[(i + 1) % data->philos_num] = 1;
		printf("i am philosopher number %d is now sleeping\n", i);
		usleep(data->time_to_sleep);
		printf("i am philosopher number %d is now thinkin\n", i);
		j++;
	}
}