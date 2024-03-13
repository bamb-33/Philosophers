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
	//the big issue here is this gettimeofday function
	//what we can do is put a lock here so only one 
	//at a time can you use it to solve the starving time variable thing
	//and in case of errors we ll try to solve that somehow
	sem_wait(data->gtod_lock);
	if (gettimeofday(tp, tzp))
	{
		printf("gettimeofday failed\n");
		gtod_failed(data, 1);//writing
		//to solve the read write operation that are simple like the one
		//above i ll make a function with flags that has locks in it.
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
