/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:47:21 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/30 14:59:46 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int		i;
	t_fork	*fork;

	data->forks = malloc(sizeof(t_fork) * data->number_of_philosophers);
	if (!data->forks)
		return (0);
	if (pthread_mutex_init(&data->dead, NULL))
		return (mutex_error(data));
	i = 0;
	while (i < data->number_of_philosophers)
	{
		fork = &data->forks[i];
		if (pthread_mutex_init(&fork->fork, NULL))
			return (mutex_error(data));
		i++;
	}
	return (1);
}

void	assign_forks(t_data *data, t_philo *philo, int *i)
{
	if (philo->index % 2 == 0)
	{
		philo->fork_1 = &data->forks[*i];
		philo->fork_2 = &data->forks[(*i + 1) % data->number_of_philosophers];
	}
	else
	{
		philo->fork_1 = &data->forks[(*i + 1) % data->number_of_philosophers];
		philo->fork_2 = &data->forks[*i];
	}
}

int	init_philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo = &data->philosophers[i];
		philo->index = i + 1;
		philo->full = false;
		philo->number_of_times_eaten = 0;
		philo->last_time_eaten = data->start;
		philo->data = data;
		philo->eating = false;
		if (pthread_mutex_init(&philo->eat, NULL))
			return (mutex_error(data));
		if (pthread_mutex_init(&philo->mtx_full, NULL))
			return (mutex_error(data));
		assign_forks(data, philo, &i);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (data->time_to_sleep < 60 || data->time_to_die < 60
		|| data->time_to_eat < 60
		|| (argc == 6 && !data->number_of_times_each_philosopher_must_eat))
		return (err_msg(data, "Overflow or less than zero error."));
	if (!data->number_of_philosophers || data->number_of_philosophers > 200)
		return (err_msg(data, "Keep philosophers between 1 and 200."));
	data->philosophers = malloc(sizeof(t_philo)
			* data->number_of_philosophers);
	if (!data->philosophers || !init_mutex(data))
		return (err_msg(data, "Allocation failure."));
	data->start = get_time();
	data->end = false;
	return (1);
}
