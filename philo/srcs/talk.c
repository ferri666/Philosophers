/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:19:35 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/27 13:47:48 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	talk(t_philo *philo, char *s)
{
	struct timeval	now;
	long long		time;

	pthread_mutex_lock(&philo->data->m_talk);
	gettimeofday(&now, NULL);
	time = time_diff(&(philo->data->start), &now);
	if (!are_you_dead(philo))
	{
		printf("%lld ms #%d %s", time, philo->id, s);
		pthread_mutex_unlock(&philo->data->m_talk);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_talk);
	return (0);
}
