/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_supervisor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:15:04 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/28 12:44:53 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_full(t_data *data)
{
	int		i;
	bool	ret;

	if (data->number_of_times_each_philosopher_must_eat == -1)
		return (false);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philosophers[i].mtx_full);
		ret = data->philosophers[i].full;
		pthread_mutex_unlock(&data->philosophers[i].mtx_full);
		if (!ret)
			return (false);
		i++;
	}
	pthread_mutex_lock(&data->dead);
	data->end = true;
	pthread_mutex_unlock(&data->dead);
	return (true);
}

bool	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philosophers[i].eat);
		if (!data->philosophers[i].eating
			&& (get_time_diff(data->philosophers[i].last_time_eaten)
				>= data->time_to_die))
		{
			print_message(&data->philosophers[i], "died");
			pthread_mutex_lock(&data->dead);
			data->end = true;
			pthread_mutex_unlock(&data->philosophers[i].eat);
			pthread_mutex_unlock(&data->dead);
			return (true);
		}
		pthread_mutex_unlock(&data->philosophers[i].eat);
		i++;
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		ft_msleep(1);
		if (check_death(data) || check_full(data))
			break ;
	}
	return (NULL);
}
