/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:28:24 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 20:29:56 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	allocating(t_philo *data, t_to_free *head)
{
	data->h_table_lock = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->h_table_lock));
	data->thread_exited_lock = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->thread_exited_lock));
	data->s_started_lock = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->s_started_lock));
	data->s_time_lock = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * data->philos_num);
	ft_lstadd_back(&head, ft_lstnew(data->s_time_lock));
}

void	mutex_init(t_philo *data, int *error)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		*error += pthread_mutex_init(&(data->h_table_lock[i]), NULL);
		*error += pthread_mutex_init(&(data->thread_exited_lock[i]), NULL);
		*error += pthread_mutex_init(&(data->s_started_lock[i]), NULL);
		*error += pthread_mutex_init(&(data->s_time_lock[i]), NULL);
		i++;
	}
	*error += pthread_mutex_init(&(data->counter_lock), NULL);
	*error += pthread_mutex_init(&(data->philo_died_lock), NULL);
	*error += pthread_mutex_init(&(data->a_t_exited_lock), NULL);
}

int	init_3_5(t_philo *data, t_to_free *head)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	allocating(data, head);
	if (!data->h_table_lock || !data->thread_exited_lock
		|| !data->s_started_lock || !data->s_time_lock)
	{
		printf("malloc failed\n");
		ft_lstclear(head);
		return (1);
	}
	mutex_init(data, &error);
	if (error < 0)
	{
		printf("pthread_mutex_init failed\n");
		ft_lstclear(head);
		return (1);
	}
	return (0);
}
