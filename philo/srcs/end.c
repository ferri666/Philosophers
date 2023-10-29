/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:05:03 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 15:56:06 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_m(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->philos[i].m_chew);
		pthread_mutex_destroy(&data->philos[i].m_death);
		pthread_mutex_destroy(&data->m_forks[i++]);
	}
}

void	destroy(t_data *data, int n)
{
	if (n < 0)
	{
		pthread_mutex_destroy(&(data->m_talk));
		pthread_mutex_destroy(&(data->m_data));
		n = data->n_philo -1;
	}
	destroy_m(data, n);
	free(data->m_forks);
	free(data->philos);
}

void	des_mut(t_data *data, int n)
{
	if (n > 1)
		pthread_mutex_destroy(&(data->m_talk));
	if (n > 2)
		pthread_mutex_destroy(&(data->m_data));
}
