/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/19 17:06:11 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_takefork(t_thdata *data)
{
	log_philo(data->pinfo, *data->philo);
	return (0);
}

int	philo_eat(t_thdata *data)
{
	log_philo(data->pinfo, *data->philo);
	return (0);
}

int	philo_sleep(t_thdata *data)
{
	log_philo(data->pinfo, *data->philo);
	return (0);
}

int	philo_think(t_thdata *data)
{
	log_philo(data->pinfo, *data->philo);
	return (0);
}

int	philo_isdied(t_thdata *data)
{
	log_philo(data->pinfo, *data->philo);
	return (0);
}

int	philo_finished(t_thdata *data)
{
	log_philo(data->pinfo, *data->philo);
	return (0);
}
