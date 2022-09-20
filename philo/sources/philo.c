/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/20 21:26:32 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_app(t_pinfo *pinfo, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < pinfo->amount)
	{
		pthread_join(philos[i].thid, NULL);
		mutex_destroy(&philos[i].lfork);
		i++;
	}
	free(philos);
	mutex_destroy(&pinfo->write);
	mutex_destroy(&pinfo->quit);
	free(pinfo);
}

static int	start_app(size_t *params, int size)
{
	t_pinfo	*pinfo;
	t_philo	*philos;

	pinfo = init_pinfo(params, size);
	if (!pinfo)
		return (0);
	philos = init_philo(pinfo);
	if (!philos)
		return (0);
	exit_app(pinfo, philos);
	return (1);
}

int	main(int ac, char **av)
{
	size_t	*params;
	int		len;

	len = ac - 1;
	params = parse_arg(av + 1, len);
	if (params && start_app(params, len))
	{
		free(params);
		return (0);
	}
	printf("Error\n");
	free(params);
	return (1);
}
