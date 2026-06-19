/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:49:06 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 17:35:30 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	even_philo_taking_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->left]);
	if (stop(data, philo))
	{
		pthread_mutex_unlock(&data->forks[philo->left]);
		return (1);
	}
	print_mutex_protect(philo, data, "has taken a fork 🥄", BLUE);
	pthread_mutex_lock(&data->forks[philo->right]);
	if (stop(data, philo))
	{
		pthread_mutex_unlock(&data->forks[philo->right]);
		pthread_mutex_unlock(&data->forks[philo->left]);
		return (1);
	}
	print_mutex_protect(philo, data, "has taken a fork 🥄", BLUE);
	return (0);
}

int	odd_philo_taking_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->right]);
	if (stop(data, philo))
	{
		pthread_mutex_unlock(&data->forks[philo->right]);
		return (1);
	}
	print_mutex_protect(philo, data, "has taken a fork 🥄", BLUE);
	pthread_mutex_lock(&data->forks[philo->left]);
	if (stop(data, philo))
	{
		pthread_mutex_unlock(&data->forks[philo->left]);
		pthread_mutex_unlock(&data->forks[philo->right]);
		return (1);
	}
	print_mutex_protect(philo, data, "has taken a fork 🥄", BLUE);
	return (0);
}

int	take_forks(t_philo *philo, t_data *data)
{
	usleep(100);
	if (philo->id % 2 == 0)
	{
		if (even_philo_taking_fork(philo, data))
			return (1);
	}
	else
	{
		if (odd_philo_taking_fork(philo, data))
			return (1);
	}
	return (0);
}

int	eat(t_philo *philo, t_data *data)
{
	usleep(100);
	if (if_dead(data))
		return (unlock_from_left_fork(data, philo), 1);
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = timestamp(data);
	philo->nb_of_meals++;
	pthread_mutex_unlock(&data->meal_mutex);
	print_mutex_protect(philo, data, "is eating 🍰", RED);
	if (usleep_in_miliseconds(data->time_to_eat, data))
		return (unlock_from_left_fork(data, philo), 1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->right]);
		pthread_mutex_unlock(&data->forks[philo->left]);
	}
	else
		unlock_from_left_fork(data, philo);
	return (0);
}

int	sleep_and_think(t_philo *philo, t_data *data)
{
	usleep(100);
	if (stop(data, philo))
		return (1);
	print_mutex_protect(philo, data, "is sleeping 💤", GREEN);
	if (usleep_in_miliseconds(data->time_to_sleep, data))
		return (1);
	if (stop(data, philo))
		return (1);
	print_mutex_protect(philo, data, "is thinking 💭", YELLOW);
	usleep(100);
	return (0);
}
