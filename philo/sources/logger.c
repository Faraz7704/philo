/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:45:45 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/20 21:42:52 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo(t_pinfo *info, t_philo *philo)
{
	size_t	timestamp;

	timestamp = philo_currt(philo);
	mutex_lock(&info->write);
	if (!info->quit.status)
	{
		if (philo->state == DIED)
			printf(RED"%zu %zu died\n", timestamp, philo->id);
		else if (philo->state == FINISHED)
			printf(ORANGE"%zu %zu has finished his meals\n", timestamp, philo->id);
		return ;
	}
	if (philo->state == TAKING_FORK)
		printf(BLUE"%zu %zu has taken a fork\n", timestamp, philo->id);
	else if (philo->state == EATING)
		printf(GREEN"%zu %zu is eating\n", timestamp, philo->id);
	else if (philo->state == SLEEPING)
		printf(CYAN"%zu %zu is sleeping\n", timestamp, philo->id);
	else if (philo->state == THINKING)
		printf(PURPLE"%zu %zu is thinking\n", timestamp, philo->id);
	mutex_unlock(&info->write);
}

// printf("amount: %zu\n", pinfo->amount);
// printf("time_to_die: %zu\n", pinfo->time_to_die);
// printf("time_to_eat: %zu\n", pinfo->time_to_eat);
// printf("time_to_sleep: %zu\n", pinfo->time_to_sleep);
// printf("amount_to_eat: %zu\n", pinfo->amount_to_eat);