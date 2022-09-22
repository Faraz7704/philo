/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:45:45 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/22 14:11:14 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo(t_pinfo *info, t_philo *philo, char *prefix, char *suffix)
{
	pthread_mutex_lock(&info->write_mutex);
	pthread_mutex_lock(&info->quit_mutex);
	if (info->quit_status)
	{
		pthread_mutex_unlock(&info->write_mutex);
		pthread_mutex_unlock(&info->quit_mutex);
		return ;
	}
	pthread_mutex_unlock(&info->quit_mutex);
	printf("%s%zu %zu %s\n", prefix, philo_currt(philo), philo->id, suffix);
	pthread_mutex_unlock(&info->write_mutex);
}
