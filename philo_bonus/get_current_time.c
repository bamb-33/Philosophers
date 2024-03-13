/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:40:57 by naadou            #+#    #+#             */
/*   Updated: 2024/03/09 18:34:10 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long int	get_current_time(struct timeval *time_start, t_philo *data)
{
	struct timeval	current_time;
	long int		time_in_micro_s;

	w_gettimeofday(&current_time, NULL, data);
	time_in_micro_s = (current_time.tv_sec * 1e6 + current_time.tv_usec)
		- (time_start->tv_sec * 1e6 + time_start->tv_usec);
	return (time_in_micro_s / 1000);
}
