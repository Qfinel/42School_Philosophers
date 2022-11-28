/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:41:27 by jtsizik           #+#    #+#             */
/*   Updated: 2022/11/27 16:53:50 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_vars *vars)
{
	int	i;

	i = 0;
	if (!vars->start_time)
		vars->start_time = get_time();
	while (i < vars->philo_num)
	{
		if (pthread_create(&vars->philos[i].thread,
				NULL, thread_handler, &vars->philos[i]))
			return (-1);
		i++;
	}
	monitoring(vars);
	join_threads(vars);
	pthread_mutex_destroy(&vars->output);
	pthread_mutex_destroy(&vars->stop);
	return (0);
}

void	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->philo_num == 1)
		pthread_detach(vars->philos[0].thread);
	while (vars->philos[i].thread)
	{
		pthread_join(vars->philos[i].thread, NULL);
		pthread_mutex_destroy(&vars->philos[i].philo_m);
		i++;
	}
	free(&vars->forks[0]);
	free(&vars->philos[0]);
}

void	monitoring(t_vars *vars)
{
	int	i;

	i = 0;
	while (!is_stopped(vars))
	{
		pthread_mutex_lock(&vars->philos[i].philo_m);
		if ((int)(get_timestamp(vars) - vars->philos[i].last_eat)
			>= vars->to_die)
		{
			stop_simulation(vars);
			output_msg(&vars->philos[i], get_timestamp(vars), 'd');
		}
		pthread_mutex_unlock(&vars->philos[i].philo_m);
		if (philos_ate(vars))
		{
			stop_simulation(vars);
			output_msg(&vars->philos[i], get_timestamp(vars), 'i');
		}
		if (i < vars->philo_num - 1)
			i++;
		else
			i = 0;
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
		return (put_error("Invalid number of args", &vars));
	if (init_vars(&vars, argc, argv) < 0)
		return (put_error("Error during initialization", &vars));
	init_philos(&vars);
	if (start_simulation(&vars) < 0)
		return (put_error("Error while creating threads", &vars));
	return (0);
}
