/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit_states.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/27 19:17:15 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pstate_died(t_pinfo *pinfo, t_philo *philo)
{
	log_philo(pinfo, philo, RED, "died");
	thsize_t_set(&pinfo->quit, 1);
	return (1);
}

int	pstate_finished(t_pinfo *pinfo, t_philo *philo)
{
	thsize_t_set(&pinfo->quit, 1);
	log_philo_woid(pinfo, philo, ORANGE, "everyone has finished their meals");
	return (1);
}
