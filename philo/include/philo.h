/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:42 by ffons-ti          #+#    #+#             */
/*   Updated: 2023/08/28 16:15:54 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				n_eats;
	struct timeval	last_meal;
	int				fork[2];
	int				status;
	int				turn;
	struct s_data	*data;
	pthread_mutex_t	m_chew;
	pthread_mutex_t	m_death;
	pthread_t		thread;
}	t_philo;

typedef struct s_data {
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				dead;
	int				n_philo;
	t_philo			*philos;
	struct timeval	start;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_talk;
	pthread_mutex_t	m_data;
	pthread_t		death;
}	t_data;

//table.c
int			create_philos(t_data *data);
int			create_forks(t_data *data);

//data.c
t_data		put_data(int ac, char **av);

//utils.c
long int	ft_atoi2(const char *str);
int			is_number(char *s);
void		ft_free_matrix(void **matrix);
int			ini_mutex(t_data *data);

//routine.c
void		*routine(void *recdata);
int			all_eaten(t_philo *philo);
int			are_you_dead(t_philo *philo);
void		psleep(t_philo *philo, struct timeval now, long long t_sleep);

//talk.c
int			talk(t_philo *philo, char *s);

//end.c
void		destroy(t_data *data, int n);
void		des_mut(t_data *data, int n);

//time.c
long long	time_diff(struct timeval *start, struct timeval *end);

//eat.c
int			eat(t_philo *ph);

//reaper.c
void		*reaper(void *recdata);
#endif