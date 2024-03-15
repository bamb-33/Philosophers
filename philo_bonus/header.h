/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:28:47 by naadou            #+#    #+#             */
/*   Updated: 2024/03/11 11:16:31 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

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
	sem_t			*gtod_lock;
	sem_t			*e_function_lock;
	sem_t			*t_exited_lock;
	sem_t			*philo_died_lock;
	pthread_t		t_id;
	struct timeval	time_start;
	struct timeval	philos_starving_time;
	t_to_free		*head;
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_philos_must_eat;
	int				thread_exited;
	int				e_function_failed;
	int				philo_died;
	int				philos_index;
	char			**av;
}	t_philo;

int			ft_atoi(const char *str, t_to_free *head);

t_philo		*init(char *av[]);
void		create_processes(t_philo *data, pid_t *pids,
				pid_t starving_time_id);

void		philos_life(t_philo *data, int i);
void		meals_time(t_philo *data);
long int	get_current_time(struct timeval *time_start, t_philo *data);
void		philosopher_status_printer(t_philo *data, int flag, int i);

sem_t	    *w_sem_open(const char *name, unsigned int value, t_philo *data, int flag);
void		*w_malloc(size_t size, t_to_free *head);
void		w_gettimeofday(struct timeval *restrict tp,
				void *restrict tzp, t_philo *data);
void		w_gettimeofday_1(struct timeval *restrict tp,
				void *restrict tzp, t_philo *data);
pid_t		w_fork(t_philo *data, int i);
void        w_sem_wait(sem_t *lock, t_philo *data, int flag);
void        w_sem_post(sem_t *lock, t_philo *data, int flag);
void        w_sem_unlink(const char *name, t_philo *data, int flag);
void        w_sem_close(sem_t *lock, t_philo *data, int flag);

int         e_function_failed(t_philo *data, int flag);
int    		thread_exited(t_philo *data, int flag);
int 		philo_died(t_philo *data, int flag);

void		ft_lstadd_back(t_to_free **lst, t_to_free *new);
void		ft_lstclear(t_to_free *lst);
t_to_free	*ft_lstnew(void *content, t_to_free *head);

#endif