/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/26 17:35:01 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pstate_start(t_pinfo *pinfo, t_philo *philo)
{
	if (philo->lfork != philo->rfork && get_forks_status(pinfo, philo))
		pstate_transition(pinfo, philo, TAKING_FORK);
	return (0);
}

int	pstate_takeforks(t_pinfo *pinfo, t_philo *philo)
{
	set_forks_status(pinfo, philo, 0);
	log_philo(pinfo, philo, BLUE, "has taken a fork");
	log_philo(pinfo, philo, BLUE, "has taken a fork");
	pstate_transition(pinfo, philo, EATING);
	return (0);
}

int	pstate_eat(t_pinfo *pinfo, t_philo *philo)
{
	log_philo(pinfo, philo, GREEN, "is eating");
	philo->last_eatt = philo_currt(philo);
	if (pinfo->time_to_eat > pinfo->time_to_die)
	{
		ft_usleep(pinfo->time_to_die);
		pstate_transition(pinfo, philo, DIED);
		return (0);
	}
	ft_usleep(pinfo->time_to_eat);
	set_forks_status(pinfo, philo, philo->id);
	pstate_transition(pinfo, philo, SLEEPING);
	update_meals(pinfo, philo);
	return (0);
}

int	pstate_sleep(t_pinfo *pinfo, t_philo *philo)
{
	log_philo(pinfo, philo, CYAN, "is sleeping");
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
	log_philo(pinfo, philo, PURPLE, "is thinking");
	pstate_transition(pinfo, philo, START);
	return (0);
}
