/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:47 by naadou            #+#    #+#             */
/*   Updated: 2024/02/23 15:59:35 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*ids;
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_philos_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	int				counter;
	int				*hash_table;
	struct timeval	*time_start;
	// pthread_t		starving_time_id;
	struct timeval	*philos_starving_time;
	int				all_threads_exited;
	int				*simulation_started;
	int				philo_died;
	int				*thread_exited;
	char			**av;
}	t_philo;

int			ft_atoi(const char *str);
void		philos_life(void *args);
void		meals_time(void *args);
long int	get_current_time(struct timeval *time_start);
void		philosopher_status_printer(t_philo *data, int flag, int i);
void		free_all(t_philo *data);

#endif