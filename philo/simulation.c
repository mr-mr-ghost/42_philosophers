/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:54:20 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/28 12:25:46 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		ft_msleep(1);
	while (!check_end(philo->data) && !check_philo_full(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	handle_1(t_data *data)
{
	t_philo	*philo;

	philo = &data->philosophers[0];
	pthread_mutex_lock(&philo->fork_1->fork);
	print_message(philo, "has taken a fork");
	ft_msleep(data->time_to_die);
	print_message(philo, "died");
	data->end = true;
	pthread_mutex_unlock(&philo->fork_1->fork);
}

int	create_threads(t_data *data)
{
	int			i;
	pthread_t	supervisor;

	if (pthread_create(&supervisor, NULL, &monitor, data))
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread_id, NULL,
				simulation, &data->philosophers[i]))
			return (0);
		i++;
	}
	if (pthread_join(supervisor, NULL))
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->philosophers[i].thread_id, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	start_simulation(t_data *data)
{
	if (data->number_of_philosophers == 1)
		handle_1(data);
	else
	{
		if (!create_threads(data))
			return (err_msg(data, "Problem creating threads"));
	}
	return (1);
}
