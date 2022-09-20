/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/20 21:29:03 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_mutex *mutex_obj)
{
	int	status;

	status = pthread_mutex_init(&mutex_obj->mutex, NULL);
	mutex_obj->status = 1;
	return (status);
}

int	mutex_trylock(t_mutex *mutex_obj)
{
	if (!mutex_obj->status)
		return (0);
	mutex_lock(mutex_obj);
	return (1);
}

void	mutex_lock(t_mutex *mutex_obj)
{
	pthread_mutex_lock(&mutex_obj->mutex);
	mutex_obj->status = 0;
}

void	mutex_unlock(t_mutex *mutex_obj)
{
	mutex_obj->status = 1;
	pthread_mutex_unlock(&mutex_obj->mutex);
}

int	mutex_destroy(t_mutex *mutex_obj)
{
	int	status;

	status = pthread_mutex_destroy(&mutex_obj->mutex);
	mutex_obj->status = 1;
	return (status);
}
