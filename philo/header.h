/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:47 by naadou            #+#    #+#             */
/*   Updated: 2024/02/20 15:20:16 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_forks
{
	struct s_forks	*previous;
	pthread_mutex_t	content;
	int				num;
	struct s_forks	*next;
}	t_forks;

typedef struct s_philo
{
	pthread_t	*ids;
	int			philos_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_times_philos_must_eat;
	t_forks		*forks;
}	t_philo;

int		ft_atoi(const char *str);
void	philos_life(void *args);

#endif