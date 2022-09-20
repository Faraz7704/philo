/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:00:57 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/20 21:26:43 by fkhan            ###   ########.fr       */
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
		pinfo->amount_to_eat = 100000;
	mutex_init(&pinfo->write);
	mutex_init(&pinfo->quit);
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
		philos[i].meals = 0;
		mutex_init(&philos[i].lfork);
		philos[i].rfork = &philos[(i + 1) % pinfo->amount].lfork;
		philos[i].state = START;
		philos[i].createdt = 0;
		philos[i].last_eatt = 0;
		if (pthread_create(&philos[i].thid, NULL,
				&philo_routine, init_thdata(pinfo, &philos[i])))
			return (0);
		i++;
	}
	return (philos);
}
