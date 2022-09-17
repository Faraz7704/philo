/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:00:57 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/17 17:51:17 by fkhan            ###   ########.fr       */
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
	pthread_mutex_init(&instance->write_mutex, NULL);
	pthread_mutex_init(&instance->die_mutex, NULL);
	return (pinfo);
}

t_thdata	init_thdata(t_pinfo *pinfo, t_philo *philo)
{
	t_thdata	data;

	data.pinfo = pinfo;
	data.philo = philo;
	return (data);
}

t_philo	*init_philo(t_pinfo *pinfo)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * pinfo->amount);
	if (!philos)
		return (0);
	i = 0;
	while (i < pinfo->amount)
	{
		philos[i].id = i;
		philos[i].lfork = i;
		philos[i].rfork = (i + 1) % pinfo->amount;
		philos[i].state = THINKING;
		pthread_create(&philos[i].thid, NULL,
			&philo_routine, init_thdata(pinfo, &philos[i]));
		i++;
	}
	return (philos);
}
