/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:47 by naadou            #+#    #+#             */
/*   Updated: 2024/02/29 14:35:10 by naadou           ###   ########.fr       */
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

typedef struct s_to_free
{
	void				*content;
	struct s_to_free	*next;
}	t_to_free;

typedef struct s_philo
{
	pid_t			*pids;
	pid_t			starving_time_id;
	sem_t			*forks;
	sem_t			lock;
	struct timeval	time_start;
	struct timeval	*philos_starving_time;
	t_to_free		*head;
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_philos_must_eat;
	int				counter;
	int				*simulation_started;
	int				all_threads_exited;
	int				philo_died;
	int				*hash_table;
	int				*thread_exited;
	char			**av;
}	t_philo;

int			ft_atoi(const char *str);
t_philo		*init(char *av[]);
int			create_threads(t_philo *data,
				pthread_t *ids, pthread_t starving_time_id);
void		philos_life(void *args);
void		meals_time(void *args);
long int	get_current_time(struct timeval *time_start);
void		philosopher_status_printer(t_philo *data, int flag, int i);

void		ft_lstadd_back(t_to_free **lst, t_to_free *new);
void		ft_lstclear(t_to_free **lst);
t_to_free	*ft_lstnew(void *content);

#endif