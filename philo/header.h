/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:47 by naadou            #+#    #+#             */
/*   Updated: 2024/03/16 21:06:13 by naadou           ###   ########.fr       */
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
	pthread_t		*ids;
	pthread_t		starving_time_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*h_table_lock;
	pthread_mutex_t	*thread_exited_lock;
	pthread_mutex_t	*s_started_lock;
	pthread_mutex_t	*s_time_lock;
	pthread_mutex_t	counter_lock;
	pthread_mutex_t	philo_died_lock;
	pthread_mutex_t	a_t_exited_lock;
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
	int				gtod_failed;
	int				*hash_table;
	int				*thread_exited;
	char			**av;
}	t_philo;

int			ft_atoi(const char *str);
t_philo		*init(char *av[]);
int			init_3_5(t_philo *data, t_to_free *head);
int			create_threads(t_philo *data,
				pthread_t *ids, pthread_t starving_time_id);
void		philos_life(void *args);
void		meals_time(void *args);
long int	get_current_time(struct timeval *time_start);
void		philosopher_status_printer(t_philo *data, int flag, int i);

int			counter(t_philo *data);
int			simulation_started(t_philo *data, int i, int flag);
int			hash_table(t_philo *data, int i, int flag);
int			philo_died(t_philo *data, int flag);
int			thread_exited(t_philo *data, int i, int flag);
int			all_threads_exited(t_philo *data, int flag);
int			gtod_failed_lock(t_philo *data, int flag);

void		ft_lstadd_back(t_to_free **lst, t_to_free *new);
void		ft_lstclear(t_to_free *lst);
t_to_free	*ft_lstnew(void *content);

#endif