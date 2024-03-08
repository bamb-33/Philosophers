/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:49:32 by naadou            #+#    #+#             */
/*   Updated: 2024/03/08 13:03:19 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_1(t_philo *data, char *av[], t_to_free *head)
{
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000; //change this later you don'y have to convert this shit
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
		ft_lstclear(&head);
		return (1);
	}
	return (0);
}

int	init_2(t_philo *data, t_to_free *head)
{
	data->pids = (pid_t *) malloc (sizeof(pid_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->pids));
	data->philos_starving_time = (struct timeval *) malloc
		(sizeof(struct timeval) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->philos_starving_time));
	data->hash_table = (int *) malloc (sizeof(int) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->hash_table));
	data->simulation_started = (int *) malloc (sizeof(int) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->simulation_started));
	data->thread_exited = (int *) malloc (sizeof(int) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->thread_exited));
	if (!data->pids || !data->philos_starving_time || !data->hash_table
		|| !data->simulation_started || !data->thread_exited)
	{
		ft_lstclear(&head);
		return (1);
	}
	data->head = head;
	return (0);
}

int	init_3(t_philo *data, t_to_free *head)
{
	data->forks = sem_open("/sem", O_CREAT, 0644, data->philos_num);
	if (data->forks == SEM_FAILED)
	{
		printf("sem_open failed\n");
		exit(0);
	}
	data->lock = sem_open("/sem_lock", O_CREAT, 0644, 1);
	if (data->lock == SEM_FAILED)
	{
		printf("sem_open failed\n");
		exit(0);
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
		ft_lstclear(&head);
		return (NULL);
	}
	if (init_1(data, av, head))
		return (NULL);
	if (init_2(data, head))
		return (NULL);
	if (init_3(data, head))
		return (NULL);
	if (init_4(data, av))
		return (NULL);
	return (data);
}
