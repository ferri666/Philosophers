/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:24 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 16:35:14 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_philo *philo)
{
	if (philo->data->n_eat > 0)
	{
		pthread_mutex_lock(&philo->m_death);
		if (philo->status == 3)
		{
			pthread_mutex_unlock(&philo->m_death);
			return (1);
		}
		if (philo->data->n_eat != philo->n_eats)
		{
			pthread_mutex_unlock(&philo->m_death);
			return (0);
		}
		else
		{
			pthread_mutex_lock(&philo->data->m_data);
			philo->status = 3;
			pthread_mutex_unlock(&philo->data->m_data);
			pthread_mutex_unlock(&philo->m_death);
			return (1);
		}
		pthread_mutex_unlock(&philo->m_death);
	}
	return (0);
}

int	are_you_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_death);
	if (philo->status == 1)
	{
		pthread_mutex_unlock(&philo->m_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_death);
	return (0);
}

void	psleep(t_philo *philo, struct timeval now, long long t_sleep)
{
	struct timeval	nnow;

	while (1)
	{
		usleep(100);
		gettimeofday(&nnow, NULL);
		if (are_you_dead(philo))
			return ;
		if (time_diff (&now, &nnow) >= t_sleep)
			return ;
	}
}

void	*routine(void *recdata)
{
	t_philo			*philo;

	philo = (t_philo *)recdata;
	philo->last_meal = philo->data->start;
	while (!are_you_dead(philo))
	{
		if (philo->turn)
			usleep(300);
		if (!eat(philo))
			return (NULL);
		if (!talk(philo, "it's thinking... 🤔\n"))
			return (NULL);
	}
	return (NULL);
}
