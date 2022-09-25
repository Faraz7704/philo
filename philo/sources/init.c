/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:00:57 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/25 19:30:08 by fkhan            ###   ########.fr       */
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
		pinfo->amount_to_eat = -1;
	pinfo->quit_status = 0;
	pinfo->finish_status = pinfo->amount;
	if (init_forks(pinfo, pinfo->amount))
	{
		free(pinfo);
		return (0);
	}
	if (pthread_mutex_init(&pinfo->finish_mutex, NULL))
	{
		free(pinfo);
		return (0);
	}
	if (pthread_mutex_init(&pinfo->write_mutex, NULL))
	{
		free(pinfo);
		return (0);
	}
	if (pthread_mutex_init(&pinfo->quit_mutex, NULL))
	{
		free(pinfo);
		return (0);
	}
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

int	init_forks(t_pinfo *pinfo, size_t size)
{
	size_t			i;

	pinfo->fork_mutexes = malloc(sizeof(pthread_mutex_t) * size);
	if (!pinfo->fork_mutexes)
		return (1);
	pinfo->forks_status = malloc(sizeof(pthread_mutex_t) * size);
	if (!pinfo->forks_status)
		return (1);
	i = 0;
	while (i < size)
	{
		pinfo->forks_status[i] = 1;
		if (pthread_mutex_init(&pinfo->fork_mutexes[i], NULL))
		{
			free(pinfo->fork_mutexes);
			free(pinfo->forks_status);
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
	if (amount % 2 == 0)
		philo->fork_value = philo->id;
	else if (i == 0)
		philo->fork_value = 2;
	else if (i == 1)
		philo->fork_value = amount;
	else if (i == amount - 1)
		philo->fork_value = 1;
	else
		philo->fork_value = philo->id;
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
