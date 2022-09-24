/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/24 20:05:02 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_quit_status(t_pinfo *pinfo)
{
	int	status;

	pthread_mutex_lock(&pinfo->quit_mutex);
	status = pinfo->quit_status;
	pthread_mutex_unlock(&pinfo->quit_mutex);
	return (!status);
}

void	set_forks_status(t_pinfo *pinfo, t_philo *philo, int value)
{
	pthread_mutex_lock(&pinfo->fork_mutexes[philo->lfork]);
	pthread_mutex_lock(&pinfo->fork_mutexes[philo->rfork]);
	pinfo->forks_status[philo->lfork] = value;
	pinfo->forks_status[philo->rfork] = value;
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->rfork]);
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->lfork]);
}

int	get_forks_status(t_pinfo *pinfo, t_philo *philo)
{
	int	status[2];

	pthread_mutex_lock(&pinfo->fork_mutexes[philo->lfork]);
	pthread_mutex_lock(&pinfo->fork_mutexes[philo->rfork]);
	status[0] = pinfo->forks_status[philo->lfork];
	status[1] = pinfo->forks_status[philo->rfork];
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->rfork]);
	pthread_mutex_unlock(&pinfo->fork_mutexes[philo->lfork]);
	return (status[0] && status[1]);
}

void	update_meals(t_pinfo *pinfo, t_philo *philo)
{
	philo->meals++;
	if (pinfo->amount_to_eat == -1)
		return ;
	pthread_mutex_lock(&pinfo->finish_mutex);
	if (philo->meals == pinfo->amount_to_eat)
	{
		if (!--pinfo->finish_status)
			pstate_transition(pinfo, philo, FINISHED);
	}
	pthread_mutex_unlock(&pinfo->finish_mutex);
}
