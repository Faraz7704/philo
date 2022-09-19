/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/19 19:51:48 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_setaction(t_philo *philo)
{
	if (philo->state == EATING)
		philo->action = &philo_eat;
	else if (philo->state == SLEEPING)
		philo->action = &philo_sleep;
	else if (philo->state == THINKING)
		philo->action = &philo_think;
	else if (philo->state == DIED)
		philo->action = &philo_isdied;
	else if (philo->state == FINISHED)
		philo->action = &philo_finished;
	else
		philo->action = &philo_takefork;
}

void	*philo_routine(void *data)
{
	t_philo	*philo;
	size_t	start_time;

	philo = ((t_thdata *)data)->philo;
	start_time = ft_get_time();
	while (1)
	{
		philo_setaction(philo);
		if (philo->action((t_thdata *)data))
			break ;
	}
	free(data);
	return (0);
}
