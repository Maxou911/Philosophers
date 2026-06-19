/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:16:17 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 16:30:25 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	timestamp(t_data *data)
{
	struct timeval	now;
	long			ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - data->start_time.tv_sec) * 1000 \
	+ (now.tv_usec - data->start_time.tv_usec) / 1000;
	return (ms);
}

int	usleep_in_miliseconds(int milliseconds, t_data *data)
{
	long	start;
	long	current;

	start = timestamp(data);
	while (1)
	{
		current = timestamp(data);
		if (current - start >= milliseconds)
			break ;
		pthread_mutex_lock(&data->state_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->state_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->state_mutex);
		usleep(100);
	}
	return (0);
}
