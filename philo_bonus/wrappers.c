/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:00:03 by naadou            #+#    #+#             */
/*   Updated: 2024/03/11 10:00:28 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

sem_t	*w_sem_open(const char *name, unsigned int value, t_to_free *head)
{
	sem_t	*result;

	result = sem_open(name, O_CREAT, 0644, value);
	if (result == SEM_FAILED)
	{
		printf("sem_open failed\n");
		ft_lstclear(&head);
		exit(1);
	}
	return (result);
}

void	*w_malloc(size_t size, t_to_free *head)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
	{
		printf("malloc failed\n");
		ft_lstclear(&head);
		exit(1);
	}
	return (result);
}

void	w_gettimeofday(struct timeval *restrict tp,
			void *restrict tzp, t_philo *data)
{
	sem_wait(data->gtod_lock);
	if (gettimeofday(tp, tzp))
	{
		printf("gettimeofday failed\n");
		gtod_failed(data, 1);
		sem_post(data->gtod_lock);
	}
	sem_post(data->gtod_lock);
}

void	w_gettimeofday_1(struct timeval *restrict tp,
			void *restrict tzp, t_philo *data)
{
	if (gettimeofday(tp, tzp))
	{
		printf("gettimeofday failed\n");
		ft_lstclear(&(data->head));
		exit(1);
	}
}

pid_t	w_fork(t_philo *data, int i)
{
	pid_t	result;

	result = fork();
	if (result < 0)
	{
		printf("fork failed\n");
		while (i)
			kill(data->pids[i--], SIGTERM);
		ft_lstclear(&(data->head));
		exit(1);
	}
	return (result);
}
