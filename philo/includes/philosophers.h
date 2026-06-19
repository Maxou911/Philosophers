/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:05:22 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 17:12:55 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>

# define RESET  "\033[0m"
# define GREEN "\033[92m"
# define RED "\033[91m"
# define YELLOW "\033[93m"
# define BLUE "\033[96m"
# define MAGENTA "\033[35m"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nb_of_meals;
	int				nb_of_meals_max;
	long			last_meal_time;
	int				right;
	int				left;
	t_data			*data;
};

struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	int				*philo_state;
	int				dead;
	struct timeval	start_time;
	pthread_t		monitor;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
};

//routine
int		has_taken_fork(t_philo *philo, t_data *data);
int		is_eating(t_philo *philo, t_data *data);
int		is_sleeping(t_philo *philo, t_data *data);
int		is_thinking(t_philo *philo, t_data *data);
void	*routine(void *arg);

//monitoring
void	*monitoring(void *arg);
int		die(t_data *data, t_philo *philo);

//init
int		init_data(t_data *data, char **av, int ac);
int		init_data_malloc(t_data *data);

//time
long	timestamp(t_data *data);
int		usleep_in_miliseconds(int miliseconds, t_data *data);

// routine utils
int		stop(t_data *data, t_philo *philo);
int		if_dead(t_data *data);
void	print_mutex_protect(t_philo *philo, t_data *data, \
	char *msg, char *color);
void	unlock_from_left_fork(t_data *data, t_philo *philo);

// routine_functions
int		take_forks(t_philo *philo, t_data *data);
int		eat(t_philo *philo, t_data *data);
int		sleep_and_think(t_philo *philo, t_data *data);

// utils
long	ft_atol(char *str);

// check_errors
int		check_errors(int ac, char **av);

#endif
