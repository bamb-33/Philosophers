/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:29 by naadou            #+#    #+#             */
/*   Updated: 2024/03/11 10:37:52 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char *av[])
{
	t_philo	*data;

	if (ac > 6 || ac < 5)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	data = init(av);
	create_processes(data, data->pids, data->starving_time_id);
	ft_lstclear(&(data->head));
	return (0);
}
