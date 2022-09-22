/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/22 14:19:38 by fkhan            ###   ########.fr       */
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
	log_philo(pinfo, philo, ORANGE, "has finished his meals");
	pthread_mutex_lock(&pinfo->quit_mutex);
	pinfo->quit_status = 1;
	pthread_mutex_unlock(&pinfo->quit_mutex);
	return (1);
}
