/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:49:32 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 20:30:16 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_1(t_philo *data, char *av[], t_to_free *head)
{
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		data->num_of_times_philos_must_eat = ft_atoi(av[5]);
	if (data->philos_num < 0
		|| data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->num_of_times_philos_must_eat < 0)
	{
		printf("invalid argument\n");
		ft_lstclear(head);
		return (1);
	}
	return (0);
}

int	init_2(t_philo *data, t_to_free *head)
{
	data->ids = (pthread_t *) malloc (sizeof(pthread_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->ids));
	data->philos_starving_time = (struct timeval *) malloc
		(sizeof(struct timeval) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->philos_starving_time));
	data->hash_table = (int *) malloc (sizeof(int) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->hash_table));
	data->simulation_started = (int *) malloc (sizeof(int) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->simulation_started));
	data->thread_exited = (int *) malloc (sizeof(int) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->thread_exited));
	if (!data->ids || !data->philos_starving_time || !data->hash_table
		|| !data->simulation_started || !data->thread_exited)
	{
		printf("malloc failed\n");
		ft_lstclear(head);
		return (1);
	}
	data->head = head;
	return (0);
}

int	init_3(t_philo *data, t_to_free *head)
{
	int		i;

	i = 0;
	data->forks = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->forks));
	if (!data->forks)
	{
		printf("malloc failed\n");
		ft_lstclear(head);
		return (1);
	}
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&(data->forks[i++]), NULL))
		{
			printf("pthread_mutex_init failed\n");
			ft_lstclear(head);
			return (1);
		}
	}
	return (0);
}

int	init_4(t_philo *data, char *av[])
{
	int	i;

	i = 0;
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
	data->counter = 0;
	data->philo_died = 0;
	data->all_threads_exited = 0;
	data->gtod_failed = 0;
	if (gettimeofday(&(data->time_start), NULL))
	{
		ft_lstclear((data->head));
		return (1);
	}
	return (0);
}

t_philo	*init(char *av[])
{
	t_philo		*data;
	t_to_free	*head;

	data = (t_philo *) malloc (sizeof(t_philo));
	head = ft_lstnew(data);
	if (!data)
	{
		ft_lstclear(head);
		return (NULL);
	}
	if (init_1(data, av, head))
		return (NULL);
	if (init_2(data, head))
		return (NULL);
	if (init_3(data, head))
		return (NULL);
	if(init_3_5(data, head))
		return (NULL);
	if (init_4(data, av))
		return (NULL);
	return (data);
}
