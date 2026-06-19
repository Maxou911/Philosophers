/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:12:12 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 17:06:39 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	die(t_data *data, t_philo *philo)
{
	long	current_time;
	long	last_meal;

	current_time = timestamp(data);
	pthread_mutex_lock(&data->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&data->meal_mutex);
	if (current_time - last_meal >= data->time_to_die)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (!data->dead)
		{
			data->dead = 1;
			print_mutex_protect(philo, data, "died ☠️", MAGENTA);
		}
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	return (0);
}

void	mutex_dead(t_data *data)
{
	pthread_mutex_lock(&data->state_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->state_mutex);
}

void	*monitoring(void *arg)
{
	t_data			*data;
	int				i;
	int				finished;

	data = (t_data *)arg;
	usleep(1000);
	while (1)
	{
		i = 0;
		finished = 0;
		while (i < data->nb_philos)
		{
			if (die(data, &data->philos[i]))
				return (NULL);
			pthread_mutex_lock(&data->meal_mutex);
			if (data->philos[i].nb_of_meals >= data->nb_of_meals \
				&& data->nb_of_meals != -1)
				finished++;
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		if (finished == data->nb_philos && data->nb_of_meals != -1)
			return (mutex_dead(data), NULL);
		usleep(100);
	}
}
