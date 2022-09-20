/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/20 21:43:22 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pstate_start(t_pinfo *pinfo, t_philo *philo)
{
	if (&philo->lfork != philo->rfork)
		pstate_transition(pinfo, philo, TAKING_FORK);
	return (0);
}

int	pstate_takeforks(t_pinfo *pinfo, t_philo *philo)
{
	mutex_lock(&philo->lfork);
	mutex_lock(philo->rfork);
	if (!is_pstate_valid(pinfo, philo))
		return (0);
	log_philo(pinfo, philo);
	log_philo(pinfo, philo);
	pstate_transition(pinfo, philo, EATING);
	return (0);
}

int	pstate_eat(t_pinfo *pinfo, t_philo *philo)
{
	size_t	eatt;
	t_state	next_state;
	size_t	timediff;

	log_philo(pinfo, philo);
	philo->meals++;
	timediff = philo_currt(philo) - philo->last_eatt;
	if (timediff + pinfo->time_to_eat > pinfo->time_to_die)
	{
		eatt = pinfo->time_to_die - timediff;
		next_state = DIED;
	}
	else
	{
		eatt = pinfo->time_to_eat;
		next_state = SLEEPING;
	}
	ft_usleep(eatt);
	philo->last_eatt = philo_currt(philo);
	mutex_unlock(philo->rfork);
	mutex_unlock(&philo->lfork);
	pstate_transition(pinfo, philo, next_state);
	return (0);
}

int	pstate_sleep(t_pinfo *pinfo, t_philo *philo)
{
	log_philo(pinfo, philo);
	if (pinfo->time_to_sleep > pinfo->time_to_die)
	{
		ft_usleep(pinfo->time_to_die);
		pstate_transition(pinfo, philo, DIED);
		return (0);
	}
	ft_usleep(pinfo->time_to_sleep);
	pstate_transition(pinfo, philo, THINKING);
	return (0);
}

int	pstate_think(t_pinfo *pinfo, t_philo *philo)
{
	log_philo(pinfo, philo);
	while (pinfo->quit.status)
	{
		if (!is_pstate_valid(pinfo, philo))
			break ;
		if (philo->lfork.status && philo->rfork->status)
		{
			pstate_transition(pinfo, philo, TAKING_FORK);
			break ;
		}
	}
	return (0);
}

int	pstate_died(t_pinfo *pinfo, t_philo *philo)
{
	mutex_lock(&pinfo->quit);
	log_philo(pinfo, philo);
	return (1);
}

int	pstate_finished(t_pinfo *pinfo, t_philo *philo)
{
	mutex_lock(&pinfo->quit);
	log_philo(pinfo, philo);
	return (1);
}
