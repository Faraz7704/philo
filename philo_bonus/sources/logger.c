/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:45:45 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/27 16:21:58 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	log_philo(t_pinfo *info, t_philo *philo, char *prefix, char *suffix)
{
	sem_wait(info->write.sem);
	if (thsize_t_get(&info->quit))
	{
		sem_post(info->write.sem);
		return ;
	}
	printf("%s%zu %zu %s\n", prefix, philo_currt(philo), philo->id, suffix);
	sem_post(info->write.sem);
}

void	log_philo_woid(t_pinfo *info, t_philo *philo,
	char *prefix, char *suffix)
{
	sem_wait(info->write.sem);
	printf("%s%zu %s\n", prefix, philo_currt(philo), suffix);
	sem_post(info->write.sem);
}
