/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/27 19:17:06 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	philo_currt(t_philo *philo)
{
	return (ft_get_time() - philo->createdt);
}

void	set_forks_status(t_pinfo *pinfo, t_philo *philo, size_t value)
{
	sem_wait(pinfo->forks[philo->lfork].sem);
	sem_wait(pinfo->forks[philo->rfork].sem);
	pinfo->forks[philo->lfork].value = value;
	pinfo->forks[philo->rfork].value = value;
	sem_post(pinfo->forks[philo->rfork].sem);
	sem_post(pinfo->forks[philo->lfork].sem);
}

static int	check_status(size_t status, t_philo *philo)
{
	return (status != philo->id && status != philo->maskout_fork);
}

int	get_forks_status(t_pinfo *pinfo, t_philo *philo)
{
	size_t	status[2];

	sem_wait(pinfo->forks[philo->lfork].sem);
	sem_wait(pinfo->forks[philo->rfork].sem);
	status[0] = pinfo->forks[philo->lfork].value;
	status[1] = pinfo->forks[philo->rfork].value;
	sem_post(pinfo->forks[philo->rfork].sem);
	sem_post(pinfo->forks[philo->lfork].sem);
	return (status[0] && status[1]
		&& (check_status(status[0], philo) || check_status(status[1], philo)));
}

void	update_meals(t_pinfo *pinfo, t_philo *philo)
{
	philo->meals++;
	if (pinfo->amount_to_eat == -1)
		return ;
	sem_wait(pinfo->finish.sem);
	if (philo->meals == pinfo->amount_to_eat && !--pinfo->finish.value)
		pstate_transition(pinfo, philo, FINISHED);
	sem_post(pinfo->finish.sem);
}
