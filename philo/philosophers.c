/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:55:49 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/30 15:01:03 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_destroy(&data->forks[i].fork);
			pthread_mutex_destroy(&data->philosophers[i].eat);
			pthread_mutex_destroy(&data->philosophers[i].mtx_full);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->dead);
	if (data->philosophers)
		free(data->philosophers);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (argc != 5 && argc != 6)
		return (err_msg(&data, "Invalid number of arguments."));
	if (!init_data(&data, argc, argv))
		return (0);
	if (!init_philosophers(&data))
		return (0);
	start_simulation(&data);
	free_data(&data);
	return (1);
}
