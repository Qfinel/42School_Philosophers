/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:58:07 by jtsizik           #+#    #+#             */
/*   Updated: 2022/11/27 16:57:38 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_handler(void *ptr)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)ptr;
	vars = philo->vars;
	if (!(philo->index % 2))
	{
		usleep(100);
		output_msg(philo, get_timestamp(vars), 't');
	}
	while (1)
	{
		start_eating(philo, vars);
		if (is_stopped(vars))
			break ;
		output_msg(philo, get_timestamp(vars), 's');
		art_sleep(vars->to_sleep);
		output_msg(philo, get_timestamp(vars), 't');
	}
	return (NULL);
}

void	start_eating(t_philo *philo, t_vars *vars)
{
	int	left_index;
	int	right_index;

	if (philo->index == 1)
		left_index = vars->philo_num - 1;
	else
		left_index = philo->index - 2;
	right_index = philo->index - 1;
	pthread_mutex_lock(&vars->forks[left_index]);
	output_msg(philo, get_timestamp(vars), 'f');
	pthread_mutex_lock(&vars->forks[right_index]);
	output_msg(philo, get_timestamp(vars), 'f');
	output_msg(philo, get_timestamp(vars), 'e');
	pthread_mutex_lock(&philo->philo_m);
	philo->last_eat = get_timestamp(vars);
	pthread_mutex_unlock(&philo->philo_m);
	art_sleep(vars->to_eat);
	pthread_mutex_lock(&philo->philo_m);
	philo->ate_num++;
	pthread_mutex_unlock(&philo->philo_m);
	pthread_mutex_unlock(&vars->forks[right_index]);
	pthread_mutex_unlock(&vars->forks[left_index]);
}

int	philos_ate(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->philos[i].index)
	{
		pthread_mutex_lock(&vars->philos[i].philo_m);
		if (vars->philos[i].ate_num < vars->must_eat)
		{
			pthread_mutex_unlock(&vars->philos[i].philo_m);
			return (0);
		}
		pthread_mutex_unlock(&vars->philos[i].philo_m);
		i++;
	}
	return (1);
}
