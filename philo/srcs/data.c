/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:29:49 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 16:15:35 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_data(t_data data)
{
	if (data.n_philo <= 0)
	{
		printf("Error: Número de filósofos inválido!! 😡\n");
		exit (-1);
	}
	if (data.t_die <= 0 || data.t_eat <= 0 || data.t_sleep <= 0)
	{
		printf("Error: That's not enough time!!! 🦆\n");
		exit (-1);
	}
	if (data.t_die >= 999999 || data.t_eat >= 999999
		|| data.t_sleep >= 999999)
	{
		printf("Error: That's too much time!!! 🦆\n");
		exit (-1);
	}
}

t_data	put_data(int ac, char **av)
{
	t_data	data;

	data.n_philo = ft_atoi2(av[1]);
	data.t_die = ft_atoi2(av[2]);
	data.t_eat = ft_atoi2(av[3]);
	data.t_sleep = ft_atoi2(av[4]);
	if (ac == 6)
	{
		data.n_eat = ft_atoi2(av[5]);
		if (data.n_eat <= 0)
		{
			printf("Error: Número de comidas inválido!!! 😡\n");
			exit (-1);
		}
	}
	else
		data.n_eat = -1;
	data.dead = 0;
	check_data(data);
	return (data);
}
