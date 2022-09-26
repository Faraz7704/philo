/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/26 20:59:12 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_set_action(t_philo *philo)
{
	if (philo->state == TAKING_FORK)
		philo->action = &pstate_takeforks;
	else if (philo->state == EATING)
		philo->action = &pstate_eat;
	else if (philo->state == SLEEPING)
		philo->action = &pstate_sleep;
	else if (philo->state == THINKING)
		philo->action = &pstate_think;
	else if (philo->state == DIED)
		philo->action = &pstate_died;
	else if (philo->state == FINISHED)
		philo->action = &pstate_finished;
	else
		philo->action = &pstate_start;
}

void	*philo_routine(void *data)
{
	t_thdata	*thdata;
	t_pinfo		*pinfo;
	t_philo		*philo;

	thdata = (t_thdata *)data;
	pinfo = thdata->pinfo;
	philo = thdata->philo;
	philo->createdt = ft_get_time();
	while (!thsize_t_get(&pinfo->quit))
	{
		is_pstate_valid(pinfo, philo);
		philo_set_action(philo);
		if (philo->action(pinfo, philo))
			break ;
		usleep(50);
	}
	free(data);
	return (NULL);
}
