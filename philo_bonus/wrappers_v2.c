/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:16:50 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 21:17:28 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	w_sem_wait(sem_t *lock, t_philo *data, int flag)
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

void	w_sem_post(sem_t *lock, t_philo *data, int flag)
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

void	w_sem_unlink(const char *name, t_philo *data, int flag)
{
	if (sem_unlink(name))
	{
		printf("sem_unlink failed\n");
		e_function_failed(data, 1);
		if (flag == 1)
		{
			ft_lstclear(data->head);
			exit(1);
		}
	}
}

void	w_sem_close(sem_t *lock, t_philo *data, int flag)
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
