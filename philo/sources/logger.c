/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:45:45 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/26 20:59:07 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo(t_pinfo *info, t_philo *philo, char *prefix, char *suffix)
{
	pthread_mutex_lock(&info->write.mutex);
	if (thsize_t_get(&info->quit))
	{
		pthread_mutex_unlock(&info->write.mutex);
		return ;
	}
	printf("%s%zu %zu %s\n", prefix, philo_currt(philo), philo->id, suffix);
	pthread_mutex_unlock(&info->write.mutex);
}

void	log_philo_woid(t_pinfo *info, t_philo *philo,
	char *prefix, char *suffix)
{
	pthread_mutex_lock(&info->write.mutex);
	printf("%s%zu %s\n", prefix, philo_currt(philo), suffix);
	pthread_mutex_unlock(&info->write.mutex);
}
