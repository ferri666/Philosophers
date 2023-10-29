/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:35:31 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 16:33:10 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	apocalypse(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->philos[i].m_death);
		data->philos[i].status = 1;
		pthread_mutex_unlock(&data->philos[i].m_death);
		pthread_mutex_unlock(&data->m_forks[i]);
		i++;
	}
	pthread_mutex_unlock(&data->m_talk);
}

static int	time_to_die(t_data *data, t_philo *philo)
{
	struct timeval	now;
	long long		nnow;
	long long		tod;

	pthread_mutex_lock(&philo->m_chew);
	gettimeofday(&now, NULL);
	nnow = time_diff(&(philo->last_meal), &now);
	pthread_mutex_unlock(&philo->m_chew);
	if (nnow > data->t_die)
	{
		pthread_mutex_lock(&philo->m_death);
		philo->status = 1;
		pthread_mutex_unlock(&philo->m_death);
		pthread_mutex_lock(&data->m_talk);
		tod = time_diff(&(philo->data->start), &now);
		printf("%lld ms #%d DIED!!!! 🕯️ 💀🕯️\n", tod, philo->id);
		return (1);
	}
	return (0);
}

int	feeded(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->m_data);
	while (data->philos[i].status == 3 && i < data->n_philo)
		i++;
	if (i == data->n_philo)
	{
		pthread_mutex_unlock(&data->m_data);
		return (1);
	}
	pthread_mutex_unlock(&data->m_data);
	return (0);
}

void	cook_reaper(t_data *data)
{
	int				i;

	i = 0;
	while (1)
	{
		if (time_to_die(data, &(data->philos[i])) || feeded(data))
			break ;
		else
			i++;
		if (i == data->n_philo)
			i = 0;
	}
}

void	*reaper(void *recdata)
{
	t_data			*data;
	int				i;

	data = (t_data *)recdata;
	i = 0;
	usleep (15);
	if (data->n_eat > 0)
		cook_reaper(data);
	else
	{
		while (1)
		{
			if (time_to_die(data, &(data->philos[i])))
				break ;
			else
				i++;
			if (i == data->n_philo)
				i = 0;
		}
	}
	apocalypse(data);
	return (NULL);
}
