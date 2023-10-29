/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:35:53 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/27 15:13:43 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL) != 0)
		{
			printf("Mutex error 🙄\n");
			destroy(data, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_forks(t_data *data)
{
	data->m_forks = malloc (sizeof(pthread_mutex_t) * data->n_philo + 1);
	if (data->m_forks == NULL)
	{
		free(data->philos);
		printf("Malloc error 🙄\n");
		return (0);
	}
	if (!init_forks(data))
		return (0);
	return (1);
}

static void	name_philo(t_philo *ph, t_data *data, int id)
{
	ph->data = data;
	ph->id = id + 1;
	ph->n_eats = 0;
	ph->fork[0] = id;
	ph->status = 0;
	if (id % 2 == 1)
		ph->turn = 1;
	else
		ph->turn = 0;
	if (id == data->n_philo - 1)
		ph->fork[1] = 0;
	else
		ph->fork[1] = id + 1;
	gettimeofday(&data->start, NULL);
	pthread_mutex_init(&ph->m_chew, NULL);
	pthread_mutex_init(&ph->m_death, NULL);
	ph->last_meal = data->start;
}

int	create_philos(t_data *data)
{
	int				i;

	data->philos = malloc (sizeof(t_philo) * (data->n_philo + 1));
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->n_philo)
	{
		name_philo(&data->philos[i], data, i);
		i++;
	}
	return (1);
}
