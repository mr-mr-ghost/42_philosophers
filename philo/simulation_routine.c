/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:24:00 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/30 14:06:59 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_full(t_philo *philo)
{
	if (philo->number_of_times_eaten
		>= philo->data->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->mtx_full);
		philo->full = true;
		pthread_mutex_unlock(&philo->mtx_full);
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->fork_1->fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_2->fork);
	if (!check_end(philo->data))
	{
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		pthread_mutex_lock(&philo->eat);
		philo->eating = true;
		pthread_mutex_unlock(&philo->eat);
		philo->last_time_eaten = get_time();
		philo->number_of_times_eaten++;
		ft_msleep(philo->data->time_to_eat);
		pthread_mutex_lock(&philo->eat);
		philo->eating = false;
		pthread_mutex_unlock(&philo->eat);
	}
	pthread_mutex_unlock(&philo->fork_2->fork);
	pthread_mutex_unlock(&philo->fork_1->fork);
	if (philo->data->number_of_times_each_philosopher_must_eat != -1)
		philo_full(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_msleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_message(philo, "is thinking");
	if (philo->data->number_of_philosophers % 2)
		ft_msleep(think_time(philo->data));
}
