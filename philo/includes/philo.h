/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:23 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/16 20:25:15 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_state
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FINISHED,
}	t_state;

typedef struct s_philo
{
	int				id;
	size_t			lfork;
	size_t			rfork;
	t_state			state;
}	t_philo;

typedef struct s_pinfo
{
	size_t			amount;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			amount_to_eat;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks_mutexes;
	pthread_mutex_t	die_mutex;
}	t_pinfo;

// logger
void		log_philo(t_pinfo *info, t_philo philo);

// init
t_pinfo		*init_pinfo(size_t *params, int size);

// parse_arg
size_t		*parse_arg(char **av, int size);

// utils
int			ft_atol(const char *string, size_t *dst);
size_t		ft_get_time(void);
void		ft_usleep(size_t ms);

#endif