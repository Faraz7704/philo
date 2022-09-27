/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:20:00 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/27 15:56:18 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atol(const char *str, size_t *dst)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+')
		i++;
	*dst = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		*dst = *dst * 10 + (str[i] - '0');
		if (*dst > __INT_MAX__)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}

size_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t ms)
{
	size_t	end;

	end = ft_get_time() + ms;
	while (ft_get_time() < end)
		usleep(ms);
}
