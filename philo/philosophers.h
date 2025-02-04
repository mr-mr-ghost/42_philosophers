/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:57:35 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/30 14:59:46 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx	fork;
}			t_fork;

typedef struct s_philo
{
	size_t		index;
	size_t		last_time_eaten;
	int			number_of_times_eaten;
	bool		eating;
	bool		full;
	t_fork		*fork_1;
	t_fork		*fork_2;
	pthread_t	thread_id;
	t_data		*data;
	t_mtx		eat;
	t_mtx		mtx_full;
}				t_philo;

struct s_data
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start;
	bool			end;
	t_fork			*forks;
	t_philo			*philosophers;
	t_mtx			dead;
};

/* initialisation */
int		init_data(t_data *data, int argc, char **argv);
int		init_mutex(t_data *data);
int		init_philosophers(t_data *data);
void	assign_forks(t_data *data, t_philo *philo, int *i);

/* utils */
int		ft_atol(const char *nptr);
int		err_msg(t_data *data, char *errmsg);
void	free_data(t_data *data);
size_t	ft_strlen(const char *s);
int		mutex_error(t_data *data);

/* time */
void	ft_msleep(size_t ms);
size_t	get_time(void);
size_t	get_time_diff(size_t start);

/* simulation */
int		start_simulation(t_data *data);
int		create_threads(t_data *data);
void	handle_1(t_data *data);
void	*simulation(void *arg);

/* simulation routine */
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_full(t_philo *philo);

/* simulation supervisor */
void	*monitor(void *arg);
void	print_message(t_philo *philo, char *message);
bool	check_full(t_data *data);
bool	check_death(t_data *data);

/* simulation utils */
bool	check_end(t_data *data);
bool	check_philo_full(t_philo *philo);
size_t	think_time(t_data *data);

#endif
