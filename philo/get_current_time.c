/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:40:57 by naadou            #+#    #+#             */
/*   Updated: 2024/02/22 09:41:16 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long int	get_current_time(struct timeval *time_start)
{
	struct timeval current_time;
	long int	time_in_micro_s;

	if (gettimeofday(&current_time, NULL))
	{
		printf("gettimeofday failed\n");
		exit(1);
	}
	time_in_micro_s = (current_time.tv_sec * 1e6 + current_time.tv_usec) - (time_start->tv_sec * 1e6 + time_start->tv_usec);
	return (time_in_micro_s / 1000);
}
