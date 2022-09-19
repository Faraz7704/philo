/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:45:45 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/19 19:49:15 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo(t_pinfo *info, t_philo philo)
{
	size_t	timestamp;

	timestamp = ft_get_time();
	pthread_mutex_lock(&info->write_mutex);
	if (philo.state == TAKING_FORK)
		printf("%zu %zu has taken a fork\n", timestamp, philo.id);
	else if (philo.state == EATING)
		printf("%zu %zu is eating\n", timestamp, philo.id);
	else if (philo.state == SLEEPING)
		printf("%zu %zu is sleeping\n", timestamp, philo.id);
	else if (philo.state == THINKING)
		printf("%zu %zu is thinking\n", timestamp, philo.id);
	else if (philo.state == DIED)
		printf("%zu %zu died\n", timestamp, philo.id);
	else if (philo.state == FINISHED)
		printf("%zu %zu has finished his meals\n", timestamp, philo.id);
	pthread_mutex_unlock(&info->write_mutex);
}

// printf("amount: %zu\n", pinfo->amount);
// printf("time_to_die: %zu\n", pinfo->time_to_die);
// printf("time_to_eat: %zu\n", pinfo->time_to_eat);
// printf("time_to_sleep: %zu\n", pinfo->time_to_sleep);
// printf("amount_to_eat: %zu\n", pinfo->amount_to_eat);