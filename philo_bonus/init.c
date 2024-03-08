/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:49:32 by naadou            #+#    #+#             */
/*   Updated: 2024/03/08 18:10:59 by naadou           ###   ########.fr       */
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
		ft_lstclear(&head);
		return (1);
	}
	return (0);
}

int	init_2(t_philo *data, t_to_free *head)
{
	data->pids = (pid_t *) malloc (sizeof(pid_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->pids));
	if (!data->pids)
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
	data->av = av;
	data->thread_exited = 0;
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
