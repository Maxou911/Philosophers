/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:17:27 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 16:30:14 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_data(t_data *data, char **av, int ac)
{
	if (check_errors(ac, av))
		return (1);
	data->dead = 0;
	data->nb_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 5)
		data->nb_of_meals = -1;
	else
		data->nb_of_meals = ft_atol(av[5]);
	if (data->nb_philos > 200 || data->nb_philos <= 0)
		return (printf("Veuillez mettre entre 1 et 200 philo\n"), 1);
	return (0);
}

int	init_data_malloc(t_data *data)
{
	data->dead = 0;
	data->philo_state = malloc(sizeof(int) * data->nb_philos);
	if (!data->philo_state)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
	{
		free(data->philo_state);
		return (1);
	}
	gettimeofday(&data->start_time, 0);
	pthread_mutex_init(&data->state_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (0);
}
