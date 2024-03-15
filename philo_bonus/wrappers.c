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

sem_t	*w_sem_open(const char *name, unsigned int value, t_philo *data, int flag)
{
	sem_t	*result;

	result = sem_open(name, O_CREAT, 0644, value);
	if (result == SEM_FAILED)
	{
		printf("sem_open failed\n");
        e_function_failed(data, 1);
        if (flag == 1)
        {
		    ft_lstclear(data->head);
		    exit(1);
        }
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
		ft_lstclear(head);
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
		e_function_failed(data, 1);
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
		ft_lstclear((data->head));
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
		ft_lstclear((data->head));
		exit(1);
	}
	return (result);
}
void    w_sem_wait(sem_t *lock, t_philo *data, int flag)
{
    if (sem_wait(lock))
    {
        printf("sem_wait failed\n");
        e_function_failed(data, 1);
        if (flag == 1)
        {
            ft_lstclear(data->head);
            exit(1);
        }
    }
}

void    w_sem_post(sem_t *lock, t_philo *data, int flag)
{
    if (sem_post(lock))
    {
        printf("sem_post failed\n");
        e_function_failed(data, 1);
        if (flag == 1)
        {
            ft_lstclear(data->head);
            exit(1);
        }
    }

}

void    w_sem_unlink(const char *name, t_philo *data, int flag)
{
    if (sem_unlink(name))
    {
        printf("sem_unlink failed\n");
        e_function_failed(data, 1);// THIS SHIT IS NOT WORKING// the probleme is when you try to unlink the same sem twice it fails cus it already got unlinked
        if (flag == 1)
        {
            ft_lstclear(data->head);
            exit(1);
        }
    }
}

void    w_sem_close(sem_t *lock, t_philo *data, int flag)
{
    if (sem_close(lock))
    {
        printf("sem_close failed\n");
        e_function_failed(data, 1);
        if (flag == 1)
        {
            ft_lstclear(data->head);
            exit(1);
        }
    }
}