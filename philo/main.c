/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:29 by naadou            #+#    #+#             */
/*   Updated: 2024/02/23 18:08:54 by naadou           ###   ########.fr       */
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

int	forks_init(t_philo *data)
{
	int		i;

	i = 0;
	data->forks = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * data->philos_num);
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&(data->forks[i++]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->lock), NULL))
		return (1);
	return (0);
}

int	init(t_philo *data, char *av[])
{
	int	i;

	i = 0;
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]); //didn't convert this one because i a not using usleep for this num
	data->time_to_eat = ft_atoi(av[3]) * 1000; //converting to milliseconde
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	data->counter = 0;
	data->hash_table = (int *) malloc (sizeof(int) * data->philos_num);
	data->simulation_started = (int *) malloc (sizeof(int) * data->philos_num);
	data->thread_exited = (int *) malloc (sizeof(int) * data->philos_num);
	data->philo_died = 0;
	while (i < data->philos_num)
	{
		if (i % 2 == 0)
			data->hash_table[i] = 1;
		else
			data->hash_table[i] = 0;
		data->simulation_started[i] = 0;
		data->thread_exited[i] = 0;
		i++;
	}
	data->av = av;
	if (av[5])
		data->num_of_times_philos_must_eat = ft_atoi(av[5]);
	data->ids = (pthread_t *) malloc (sizeof(pthread_t) * data->philos_num);
	data->philos_starving_time = (struct timeval *) malloc (sizeof(struct timeval) * data->philos_num);
	data->all_threads_exited = 0;
	if (forks_init(data))
		return (1);
	return (0);
}

int	create_threads(t_philo *data, pthread_t *ids, pthread_t starving_time_id)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_create(&(ids[i++]), NULL, (void *) philos_life, data))
			return (1);
	}
	simulation_started(data);
	if (pthread_create(&starving_time_id, NULL, (void *) meals_time, data))
		return (1);
	while (i)
		pthread_join(ids[--i], NULL);
	data->all_threads_exited = 1;
	pthread_join(starving_time_id, NULL);
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	*data;

	data = (t_philo *) malloc (sizeof(t_philo));
	data->time_start = (struct timeval *) malloc (sizeof(struct timeval));
	gettimeofday(data->time_start, NULL);
	if (ac > 6)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	if (init(data, av))
		return (1);
	create_threads(data, data->ids, data->starving_time_id);
	free_all(data);
	return (0);
}
