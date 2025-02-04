/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoddy <jhoddy@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:08:12 by jhoddy            #+#    #+#             */
/*   Updated: 2024/10/30 14:58:38 by jhoddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	err_msg(t_data *data, char *errmsg)
{
	write(2, "ERROR:\n", 7);
	write(2, errmsg, ft_strlen(errmsg));
	write(2, "\n", 1);
	if (data)
	{
		if (data->forks)
			free(data->forks);
		if (data->philosophers)
			free(data->philosophers);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_atol(const char *nptr)
{
	int		i;
	long	result;

	if (ft_strlen(nptr) > 11)
		return (0);
	i = 0;
	result = 0;
	while (nptr[i] <= 32 && nptr[i] != 27 && nptr[i] != 8)
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + nptr[i++] - '0';
	if (result <= 0 || result > INT_MAX)
		return (0);
	return ((int)result);
}

int	mutex_error(t_data *data)
{
	free_data(data);
	write(2, "ERROR:\nMutex initialization failure.\n", 36);
	return (0);
}
