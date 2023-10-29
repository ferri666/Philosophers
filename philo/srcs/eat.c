/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:05:53 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 16:30:09 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	return_forks(t_philo *philo)
{
	struct timeval	nap_time;

	gettimeofday(&nap_time, NULL);
	talk(philo, "it's sleeping... 😴\n");
	pthread_mutex_unlock(&philo->data->m_forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->m_forks[philo->fork[0]]);
	psleep(philo, nap_time, philo->data->t_sleep);
	philo->turn = 1;
}

static void	this_fork(t_philo *ph, int fork)
{
	pthread_mutex_lock(&ph->data->m_forks[fork]);
	talk(ph, "has taken a fork 🍴\n");
}

static int	finish_eating(t_philo *ph)
{
	ph->n_eats++;
	if (ph->n_eats == ph->data->n_eat)
		all_eaten(ph);
	return_forks(ph);
	return (1);
}

static int	chew(t_philo *ph)
{
	pthread_mutex_lock(&ph->m_chew);
	gettimeofday(&ph->last_meal, NULL);
	pthread_mutex_unlock(&ph->m_chew);
	if (!talk (ph, "it's eating      🍝\n"))
		return (0);
	psleep(ph, ph->last_meal, ph->data->t_eat);
	if (!are_you_dead(ph))
		finish_eating(ph);
	else
		return (0);
	return (1);
}

int	eat(t_philo *ph)
{
	this_fork(ph, ph->fork[0]);
	this_fork(ph, ph->fork[1]);
	if (!chew(ph))
	{
		return_forks(ph);
		return (0);
	}
	return (1);
}
