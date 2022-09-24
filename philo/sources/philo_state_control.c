/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/24 20:04:49 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_pstate_valid(t_pinfo *pinfo, t_philo *philo)
{
	if (philo_currt(philo) - philo->last_eatt >= pinfo->time_to_die)
	{
		philo->state = DIED;
		return (0);
	}
	return (1);
}

int	pstate_transition(t_pinfo *pinfo, t_philo *philo, t_state next_state)
{
	(void)pinfo;
	philo->state = next_state;
	return (1);
}
