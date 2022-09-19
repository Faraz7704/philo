/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:00:57 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/19 19:52:00 by fkhan            ###   ########.fr       */
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
		pinfo->amount_to_eat = 0;
	pinfo->forks_mutexes = init_forks_mutexes(pinfo->amount);
	if (!pinfo->forks_mutexes)
		return (0);
	pthread_mutex_init(&pinfo->write_mutex, NULL);
	pthread_mutex_init(&pinfo->die_mutex, NULL);
	pthread_mutex_init(&g_write_mutex, NULL);
	return (pinfo);
}

pthread_mutex_t	*init_forks_mutexes(int size)
{
	pthread_mutex_t	*forks_mutexes;
	int				i;

	forks_mutexes = malloc(sizeof(pthread_mutex_t) * size);
	if (!forks_mutexes)
		return (0);
	i = 0;
	while (i < size)
		pthread_mutex_init(&forks_mutexes[i++], NULL);
	return (forks_mutexes);
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

t_philo	*init_philo(t_pinfo *pinfo)
{
	size_t	i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * pinfo->amount);
	if (!philos)
		return (0);
	i = 0;
	printf("amount: %zu\n", pinfo->amount);
	while (i < pinfo->amount)
	{
		philos[i].id = i;
		philos[i].lfork_index = i;
		philos[i].rfork_index = (i + 1) % pinfo->amount;
		philos[i].state = TAKING_FORK;
		if (pthread_create(&philos[i].thid, NULL,
				&philo_routine, init_thdata(pinfo, &philos[i])))
			return (0);
		i++;
	}
	return (philos);
}
