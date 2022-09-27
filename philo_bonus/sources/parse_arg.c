/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:00:57 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/27 15:56:30 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	*parse_arg(char **av, int size)
{
	int		i;
	size_t	*new;

	if (!size)
		return (0);
	new = malloc(sizeof(size_t) * size);
	if (!new)
		return (0);
	i = 0;
	while (i < size)
	{
		if (!ft_atol(av[i], &new[i]))
		{
			free(new);
			return (0);
		}
		i++;
	}
	return (new);
}
