/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_time_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:55:16 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/30 14:55:16 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_time_diff(size_t start)
{
	return (get_time() - start);
}

void	ft_msleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(500);
}

size_t	think_time(t_data *data)
{
	long	time_to_think;

	time_to_think = (data->time_to_eat * 2) - data->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	return (time_to_think);
}
