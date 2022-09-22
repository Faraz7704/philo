/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/22 14:39:38 by fkhan            ###   ########.fr       */
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

static int	validate_routine(t_pinfo *pinfo, t_philo *philo)
{
	pthread_mutex_lock(&pinfo->quit_mutex);
	if (pinfo->quit_status)
	{
		if (philo->state == EATING)
		{
			pthread_mutex_unlock(&pinfo->fork_mutexes[philo->rfork]);
			pthread_mutex_unlock(&pinfo->fork_mutexes[philo->lfork]);
		}
		pthread_mutex_unlock(&pinfo->quit_mutex);
		return (0);
	}
	pthread_mutex_unlock(&pinfo->quit_mutex);
	return (1);
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
	while (1)
	{
		is_pstate_valid(pinfo, philo);
		philo_set_action(philo);
		if (philo->action(pinfo, philo) || !validate_routine(pinfo, philo))
			break ;
	}
	free(data);
	return (NULL);
}
