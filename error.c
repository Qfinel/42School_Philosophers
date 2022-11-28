/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:59:37 by jtsizik           #+#    #+#             */
/*   Updated: 2022/11/27 12:58:16 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_error(char *str, t_vars *vars)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	if (vars->philos)
		free_err(vars);
	return (-1);
}

void	free_err(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->philos[0].index)
	{
		free(&vars->forks[0]);
		free(&vars->philos[0]);
	}
}
