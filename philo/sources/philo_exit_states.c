/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit_states.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/25 20:01:18 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pstate_died(t_pinfo *pinfo, t_philo *philo)
{
	log_philo(pinfo, philo, RED, "died");
	pthread_mutex_lock(&pinfo->quit_mutex);
	pinfo->quit_status = 1;
	pthread_mutex_unlock(&pinfo->quit_mutex);
	return (1);
}

int	pstate_finished(t_pinfo *pinfo, t_philo *philo)
{
	pthread_mutex_lock(&pinfo->write_mutex);
	printf(ORANGE"%zu everyone has finished their meals\n", philo_currt(philo));
	pthread_mutex_unlock(&pinfo->write_mutex);
	pthread_mutex_lock(&pinfo->quit_mutex);
	pinfo->quit_status = 1;
	pthread_mutex_unlock(&pinfo->quit_mutex);
	return (1);
}
