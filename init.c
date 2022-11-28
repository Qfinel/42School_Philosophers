/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:41:14 by jtsizik           #+#    #+#             */
/*   Updated: 2022/11/24 13:31:17 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_vars(t_vars *vars, int argc, char **argv)
{
	vars->philo_num = ft_atoi(argv[1]);
	vars->to_die = ft_atoi(argv[2]);
	vars->to_eat = ft_atoi(argv[3]);
	vars->to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		vars->must_eat = ft_atoi(argv[5]);
	if (vars->philo_num < 1 || vars->to_eat < 1
		|| vars->to_die < 1 || vars->to_sleep < 1
		|| (argc == 6 && vars->must_eat < 1))
		return (-1);
	if (init_mutexes(vars) < 0)
		return (-1);
	return (0);
}

int	init_mutexes(t_vars *vars)
{
	int	i;

	vars->forks = malloc(vars->philo_num * (sizeof(pthread_mutex_t)));
	vars->philos = malloc(vars->philo_num * sizeof(t_philo));
	if (!vars->forks || !vars->philos)
		return (-1);
	i = 0;
	while (i < vars->philo_num)
	{
		if (pthread_mutex_init(&vars->philos[i].philo_m, NULL))
			return (-1);
		if (pthread_mutex_init(&vars->forks[i], NULL))
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&vars->output, NULL)
		|| pthread_mutex_init(&vars->stop, NULL))
		return (-1);
	return (0);
}

void	init_philos(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_num)
	{
		vars->philos[i].index = i + 1;
		vars->philos[i].ate_num = 0;
		vars->philos[i].vars = vars;
		i++;
	}
}
