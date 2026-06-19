/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:04:53 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 16:30:16 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_and_destroy(t_data *data)
{
	free(data->forks);
	free(data->philo_state);
	pthread_mutex_destroy(&data->state_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

int	init_create_and_join(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].id = i;
		philos[i].nb_of_meals = 0;
		philos[i].last_meal_time = timestamp(data);
		philos[i].data = data;
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (printf("Failed to create thread\n"), 1);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitoring, data) != 0)
		return (printf("Failed to create monitor thread\n"), 1);
	if (pthread_join(data->monitor, NULL) != 0)
		return (printf("Failed to join monitor thread\n"), 1);
	return (0);
}

int	join_and_clean(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (printf("Failed to join thread\n"), 1);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philos;
	t_data			data;

	if (init_data(&data, av, ac))
		return (1);
	philos = malloc(sizeof(t_philo) * data.nb_philos);
	if (!philos)
		return (1);
	data.philos = philos;
	if (init_data_malloc(&data))
		return (printf("Erreur d'initialisation\n"), 1);
	if (init_create_and_join(&data, philos))
		return (1);
	if (join_and_clean(&data, philos))
		return (1);
	free(philos);
	free_and_destroy(&data);
	return (0);
}
