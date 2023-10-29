/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:24:42 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 17:33:35 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < 48 || *s > 57)
			return (0);
		s++;
	}
	return (1);
}

void	ft_free_matrix(void **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
}

static int	ft_spaces(const char *str)
{
	int	sp_nb;

	sp_nb = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\f'
		|| *str == '\v' || *str == '\r')
	{
		sp_nb++;
		str++;
	}
	return (sp_nb);
}

long int	ft_atoi2(const char *str)
{
	int				sign;
	long int		num;
	int				n;

	sign = 1;
	num = 0;
	n = ft_spaces(str);
	if (str[n] == '-' || str[n] == '+')
	{
		if (str[n] == '-')
			sign *= -1;
		n++;
	}
	while (str[n] >= '0' && str[n] <= '9')
	{
		num *= 10;
		num += str[n] - '0';
		n++;
	}
	num *= sign;
	if (num > 2147483647)
		return (2147483647);
	if (num < -2147483648)
		return (-2147483648);
	return (num);
}

int	ini_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_talk, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->m_data, NULL) != 0)
		return (2);
	return (0);
}
