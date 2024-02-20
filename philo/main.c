/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:29 by naadou            #+#    #+#             */
/*   Updated: 2024/02/20 17:25:46 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_forks	*new_node(t_forks *previous_node)
{
	t_forks	*new_node;

	new_node = (t_forks *) malloc (sizeof(t_forks));
	previous_node->next = new_node;
	new_node->previous = previous_node;
	return (new_node);
}

int	forks_init(t_philo *data, t_forks *forks)
{
	int		i;
	t_forks *head;

	i = 0;
	head = forks;
	while (i < data->philos_num - 1)
	{
		if (pthread_mutex_init(&(forks->content), NULL))
			return (1);
		forks->num = i + 1;
		forks = new_node(forks);
		i++;
		forks->num = i + 1;
	}
	forks->next = head;
	head->previous = forks;
	forks = forks->next;
	return (0);
}

int	init(t_philo *data, char *av[])
{
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->num_of_times_philos_must_eat = ft_atoi(av[5]);
	data->ids = (pthread_t *) malloc (sizeof(pthread_t) * data->philos_num);
	if (forks_init(data, data->forks))
		return (1);
	return (0);
}

int	create_threads(t_philo *data, t_forks *forks, pthread_t *ids)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_create(&(ids[i++]), NULL, (void *) philos_life, data))
			return (1);
	}
	while (i)
		pthread_join(ids[--i], NULL);
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	*data;

	data = (t_philo *) malloc (sizeof(t_philo));
	data->forks = (t_forks *) malloc (sizeof(t_forks));
	if (ac > 6)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	if (init(data, av))
		return (1);
	create_threads(data, data->forks, data->ids);
	return (0);
}