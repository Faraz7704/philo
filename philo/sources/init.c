/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:00:57 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/22 14:22:43 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pinfo	*init_pinfo(size_t *params, int size)
{
	t_pinfo	*pinfo;

	if (size < 4)
		return (0);
	pinfo = malloc(sizeof(t_pinfo));
	if (!pinfo)
		return (0);
	pinfo->amount = params[0];
	pinfo->time_to_die = params[1];
	pinfo->time_to_eat = params[2];
	pinfo->time_to_sleep = params[3];
	if (size > 4)
		pinfo->amount_to_eat = params[4];
	else
		pinfo->amount_to_eat = 4294967295;
	pinfo->quit_status = 0;
	if (init_forks(&pinfo->fork_mutexes, pinfo->amount))
		return (0);
	if (pthread_mutex_init(&pinfo->write_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&pinfo->quit_mutex, NULL))
		return (0);
	return (pinfo);
}

t_thdata	*init_thdata(t_pinfo *pinfo, t_philo *philo)
{
	t_thdata	*data;

	data = malloc(sizeof(t_thdata));
	if (!data)
		exit(1);
	data->pinfo = pinfo;
	data->philo = philo;
	return (data);
}

int	init_forks(pthread_mutex_t **forks, size_t size)
{
	size_t			i;

	forks[0] = malloc(sizeof(pthread_mutex_t) * size);
	if (!forks)
		return (1);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&forks[0][i], NULL))
		{
			free(forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	setforks(t_philo *philo, int i, int amount)
{
	if (philo->id % 2)
	{
		philo->lfork = i;
		philo->rfork = (i + 1) % amount;
	}
	else
	{
		philo->lfork = (i - 1) % amount;
		philo->rfork = i;
	}
}

t_philo	*init_philo(t_pinfo *pinfo)
{
	size_t	i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * pinfo->amount);
	if (!philos)
		return (0);
	i = 0;
	while (i < pinfo->amount)
	{
		philos[i].id = i + 1;
		setforks(&philos[i], i, pinfo->amount);
		philos[i].meals = 0;
		philos[i].state = START;
		philos[i].createdt = 0;
		philos[i].last_eatt = 0;
		i++;
	}
	return (philos);
}
