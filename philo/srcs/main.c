/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:20:59 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 16:14:16 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong number of variables! 😡\n");
		exit (-1);
	}
	while (++i < ac)
	{
		if (!is_number(av[i]))
		{
			printf(" \"%s\" is not a number!  🤬\n", av[i]);
			exit(-1);
		}
	}
}

static int	join(t_data *data)
{
	int	n;

	n = 0;
	while (n < data->n_philo)
	{
		if (pthread_join(data->philos[n].thread, NULL) != 0)
			return (0);
		n++;
	}
	return (1);
}

static int	alone(t_data *data)
{
	int			n;

	n = ini_mutex(data);
	if (n != 0)
	{
		des_mut(data, n);
		return (0);
	}
	gettimeofday(&data->start, NULL);
	if (pthread_create(&data->philos[0].thread,
			NULL, &routine, (void *) &data->philos[0]) != 0)
		return (0);
	if (pthread_create(&data->death,
			NULL, &reaper, (void *) data) != 0)
		return (0);
	if (pthread_join(data->philos[0].thread, NULL) != 0)
		return (0);
	if (pthread_join(data->death, NULL) != 0)
		return (0);
	return (1);
}

static int	begin(t_data *data)
{
	int	n;

	n = ini_mutex(data);
	if (n != 0)
	{
		des_mut(data, n);
		return (0);
	}
	gettimeofday(&data->start, NULL);
	while (n < data->n_philo)
	{
		if (pthread_create(&data->philos[n].thread,
				NULL, &routine, (void *) &data->philos[n]) != 0)
			return (0);
		n++;
	}
	if (pthread_create(&data->death,
			NULL, &reaper, (void *) data) != 0)
		return (0);
	if (!join(data))
		return (0);
	if (pthread_join(data->death, NULL) != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;

	check_args(ac, av);
	data = put_data(ac, av);
	if (!create_philos(&data))
		return (1);
	if (!create_forks(&data))
		return (1);
	if (data.n_philo == 1)
	{
		if (alone(&data) < 1)
			destroy(&data, -1);
		else
			destroy(&data, 1);
		return (0);
	}
	if (begin(&data) < 1)
		destroy(&data, -1);
	else
		destroy(&data, data.n_philo);
	return (0);
}
