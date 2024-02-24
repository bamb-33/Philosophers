/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:29 by naadou            #+#    #+#             */
/*   Updated: 2024/02/24 20:48:13 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char *av[])
{
	t_philo	*data;

	if (ac > 6)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	data = init(av);
	if (!data)
	{
		return (1);
	}
	if (create_threads(data, data->ids, data->starving_time_id))
		return (1);
	ft_lstclear(&(data->head));
	return (0);
}
