/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:28:05 by jtsizik           #+#    #+#             */
/*   Updated: 2022/11/27 13:00:18 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	num;
	int	mult;

	i = 0;
	num = 0;
	mult = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] != '\0')
		return (0);
	i--;
	while (i >= 0 && (str[i] >= '0' && str[i] <= '9'))
	{
		num += (str[i] - 48) * mult;
		mult *= 10;
		i--;
	}
	return (num);
}

void	output_msg(t_philo *philo, unsigned long time, char d)
{
	pthread_mutex_lock(&philo->vars->output);
	if (d == 'd')
		printf("%lu %d died\n", time, philo->index);
	if (d == 'i')
		printf("%lu all philosophers ate enough\n", time);
	if (is_stopped(philo->vars))
	{
		pthread_mutex_unlock(&philo->vars->output);
		return ;
	}
	if (d == 'f')
		printf("%lu %d has taken a fork\n", time, philo->index);
	if (d == 'e')
		printf("%lu %d is eating\n", time, philo->index);
	if (d == 's')
		printf("%lu %d is sleeping\n", time, philo->index);
	if (d == 't')
		printf("%lu %d is thinking\n", time, philo->index);
	pthread_mutex_unlock(&philo->vars->output);
}

void	stop_simulation(t_vars *vars)
{
	pthread_mutex_lock(&vars->stop);
		vars->stopped = 1;
	pthread_mutex_unlock(&vars->stop);
}

int	is_stopped(t_vars *vars)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&vars->stop);
	if (vars->stopped == 1)
		flag = 1;
	pthread_mutex_unlock(&vars->stop);
	return (flag);
}
