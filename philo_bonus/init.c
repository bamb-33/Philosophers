/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:49:32 by naadou            #+#    #+#             */
/*   Updated: 2024/03/19 00:52:46 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_philo	*init(char *av[])
{
	t_philo		*data;
	t_to_free	*head;

	data = (t_philo *) w_malloc (sizeof(t_philo), NULL);
	head = NULL;
	head = ft_lstnew(data, head);
	data->philos_num = ft_atoi(av[1], head);
	data->time_to_die = ft_atoi(av[2], head);
	data->time_to_eat = ft_atoi(av[3], head) * 1000;
	data->time_to_sleep = ft_atoi(av[4], head) * 1000;
	if (av[5])
		data->num_of_times_philos_must_eat = ft_atoi(av[5], head);
	data->pids = (pid_t *) w_malloc (sizeof(pid_t) * data->philos_num, head);
	ft_lstadd_back(&head, ft_lstnew(data->pids, head));
	data->forks = w_sem_open("/sem", data->philos_num, data, 0);
	data->test_lock = w_sem_open("/sem_test_lock", 1, data, 0);
	data->head = head;
	data->av = av;
	data->thread_exited = 0;
	data->e_function_failed = 0;
	data->philo_died = 0;
	return (data);
}
