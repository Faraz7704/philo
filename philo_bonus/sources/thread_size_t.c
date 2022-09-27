/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_size_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/27 19:11:30 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	thsize_t_init(t_thsize_t *data, char *data_name, size_t value)
{
	data->value = value;
	sem_unlink(data_name);
	data->sem = sem_open(data_name, O_CREAT, 0600, 1);
	if (!data->sem)
		return (1);
	return (0);
}

void	thsize_t_set(t_thsize_t *data, size_t value)
{
	sem_wait(data->sem);
	data->value = value;
	sem_post(data->sem);
}

size_t	thsize_t_get(t_thsize_t *data)
{
	size_t	value;

	sem_wait(data->sem);
	value = data->value;
	sem_post(data->sem);
	return (value);
}

int	thsize_t_destroy(t_thsize_t *data, size_t value)
{
	data->value = value;
	return (sem_close(data->sem));
}
