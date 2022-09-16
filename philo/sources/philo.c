/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/16 20:25:40 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start(size_t *params, int size)
{
	t_pinfo	*pinfo;

	pinfo = init_pinfo(params, size);
	if (!pinfo)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	size_t	*params;
	int		len;

	len = ac - 1;
	params = parse_arg(av + 1, len);
	if (params && start(params, len))
	{
		free(params);
		return (0);
	}
	printf("Error\n");
	free(params);
	return (0);
}
