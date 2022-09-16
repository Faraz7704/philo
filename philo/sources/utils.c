/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:20:00 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/16 20:08:05 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *string, size_t *dst)
{
	int	i;

	i = 0;
	if (string[i] == '\0')
		return (0);
	*dst = 0;
	while (string[i] && string[i] >= '0' && string[i] <= '9')
	{
		*dst = *dst * 10 + (string[i] - '0');
		i++;
	}
	if (string[i] != '\0')
		return (0);
	return (1);
}

size_t	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t ms)
{
	size_t	end;

	end = ft_get_time() + ms;
	while (ft_get_time() < end)
		usleep(ms / 1000);
}
