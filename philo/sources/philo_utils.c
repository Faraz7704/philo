/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/25 19:32:54 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	philo_currt(t_philo *philo)
{
	return (ft_get_time() - philo->createdt);
}

void	set_forks_status(t_pinfo *pinfo, t_philo *philo, size_t value)
{
	pthread_mutex_lock(&pinfo->fork_mutexes[philo->lfork]);
	pthread_mutex_lock(&pinfo->fork_mutexes[philo->rfork]);
	pinfo->forks_status[philo->lfork] = value;
	pinfo->forks_status[philo->rfork] = value;
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->rfork]);
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->lfork]);
}

static int	check_status(size_t status, t_philo *philo)
{
	return (status != philo->id && status != philo->fork_value);
}

int	get_forks_status(t_pinfo *pinfo, t_philo *philo)
{
	size_t	status[2];

	pthread_mutex_lock(&pinfo->fork_mutexes[philo->lfork]);
	pthread_mutex_lock(&pinfo->fork_mutexes[philo->rfork]);
	status[0] = pinfo->forks_status[philo->lfork];
	status[1] = pinfo->forks_status[philo->rfork];
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->rfork]);
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->lfork]);
	return (status[0] && status[1]
		&& (check_status(status[0], philo) || check_status(status[1], philo)));
}

void	update_meals(t_pinfo *pinfo, t_philo *philo)
{
	philo->meals++;
	if (pinfo->amount_to_eat == -1)
		return ;
	pthread_mutex_lock(&pinfo->finish_mutex);
	if (philo->meals == pinfo->amount_to_eat && !--pinfo->finish_status)
		pstate_transition(pinfo, philo, FINISHED);
	pthread_mutex_unlock(&pinfo->finish_mutex);
}
