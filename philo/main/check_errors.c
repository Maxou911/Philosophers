/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:08:33 by maalwis           #+#    #+#             */
/*   Updated: 2025/08/29 16:30:03 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_number(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == '-')
			return (1);
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_limit(char *s)
{
	long	num;

	num = ft_atol(s);
	if (num < INT_MIN || num > INT_MAX)
		return (1);
	if (num != ft_atol(s))
		return (1);
	return (0);
}

int	check_errors(int ac, char **av)
{
	int	i;
	int	*numbers;

	i = 1;
	numbers = malloc(sizeof(int) * ac);
	if (!numbers)
		return (1);
	if (ac < 5 || ac > 6)
		return (free(numbers), printf("Veuillez mettre 5 ou 6 arguments\n"), 1);
	while (i < ac)
	{
		if (check_number(av[i]) || check_limit(av[i]))
		{
			free(numbers);
			printf("Veuillez mettre un nombre positif \
et ne pas depasser les limites\n");
			return (1);
		}
		numbers[i] = ft_atol(av[i]);
		i++;
	}
	free(numbers);
	return (0);
}
