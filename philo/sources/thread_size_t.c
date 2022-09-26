/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_size_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/26 20:58:42 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thsize_t_init(t_thsize_t *data, size_t value)
{
	data->value = value;
	return (pthread_mutex_init(&data->mutex, NULL));
}

void	thsize_t_set(t_thsize_t *data, size_t value)
{
	pthread_mutex_lock(&data->mutex);
	data->value = value;
	pthread_mutex_unlock(&data->mutex);
}

size_t	thsize_t_get(t_thsize_t *data)
{
	size_t	value;

	pthread_mutex_lock(&data->mutex);
	value = data->value;
	pthread_mutex_unlock(&data->mutex);
	return (value);
}

int	thsize_t_destroy(t_thsize_t *data, size_t value)
{
	data->value = value;
	return (pthread_mutex_destroy(&data->mutex));
}
