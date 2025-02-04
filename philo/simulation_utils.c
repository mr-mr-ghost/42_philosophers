/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:19:37 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/30 14:58:38 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->dead);
	if (!philo->data->end)
		printf("%ld: Philosopher %ld %s\n",
			get_time_diff(philo->data->start), philo->index, message);
	pthread_mutex_unlock(&philo->data->dead);
}

bool	check_end(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->dead);
	ret = data->end;
	pthread_mutex_unlock(&data->dead);
	return (ret);
}

bool	check_philo_full(t_philo *philo)
{
	bool	ret;

	if (philo->data->number_of_times_each_philosopher_must_eat == -1)
		return (false);
	pthread_mutex_lock(&philo->mtx_full);
	ret = philo->full;
	pthread_mutex_unlock(&philo->mtx_full);
	return (ret);
}
