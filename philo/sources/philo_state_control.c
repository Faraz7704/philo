/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/22 14:44:27 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_locks(t_pinfo *pinfo, t_philo *philo)
{
	if (philo->state == EATING)
	{
		pthread_mutex_unlock(&pinfo->fork_mutexes[philo->rfork]);
		pthread_mutex_unlock(&pinfo->fork_mutexes[philo->lfork]);
	}
}

int	is_pstate_valid(t_pinfo *pinfo, t_philo *philo)
{
	if (philo_currt(philo) - philo->last_eatt >= pinfo->time_to_die)
	{
		cleanup_locks(pinfo, philo);
		philo->state = DIED;
		return (0);
	}
	if (philo->meals >= pinfo->amount_to_eat)
	{
		cleanup_locks(pinfo, philo);
		philo->state = FINISHED;
		return (0);
	}
	return (1);
}

int	pstate_transition(t_pinfo *pinfo, t_philo *philo, t_state next_state)
{
	philo->state = next_state;
	return (is_pstate_valid(pinfo, philo));
}
