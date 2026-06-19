/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:46:26 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 17:08:43 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	if_dead(t_data *data)
{
	pthread_mutex_lock(&data->state_mutex);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

int	if_max_meals_reached(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (data->nb_of_meals != -1 && \
		philo->nb_of_meals >= data->nb_of_meals)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (0);
}

int	stop(t_data *data, t_philo *philo)
{
	if (if_dead(data) || if_max_meals_reached(data, philo))
		return (1);
	return (0);
}

void	print_mutex_protect(t_philo *philo, t_data *data, \
	char *msg, char *color)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ldms%s %d %s%s\n", timestamp(data), color, \
	philo->id + 1, msg, RESET);
	pthread_mutex_unlock(&data->print_mutex);
}

void	unlock_from_left_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&data->forks[philo->left]);
	pthread_mutex_unlock(&data->forks[philo->right]);
}
