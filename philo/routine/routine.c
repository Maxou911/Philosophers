/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:25:16 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 16:53:51 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->left = philo->id;
	philo->right = (philo->id + 1) % data->nb_philos;
	if (data->nb_philos == 1)
	{
		printf("%ldms"BLUE" 1 has taken a fork\n"RESET, timestamp(data));
		usleep_in_miliseconds(data->time_to_die, data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!stop(data, philo))
	{
		if (take_forks(philo, data))
			break ;
		if (eat(philo, data))
			break ;
		if (sleep_and_think(philo, data))
			break ;
	}
	return (NULL);
}
