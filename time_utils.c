/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:04:56 by jtsizik           #+#    #+#             */
/*   Updated: 2022/11/28 16:00:38 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (miliseconds);
}

unsigned long	get_timestamp(t_vars *vars)
{
	struct timeval	now;
	unsigned long	miliseconds;

	gettimeofday(&now, NULL);
	miliseconds = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	pthread_mutex_lock(&vars->stop);
	miliseconds = miliseconds - vars->start_time;
	pthread_mutex_unlock(&vars->stop);
	return (miliseconds);
}

void	art_sleep(int milisec)
{
	unsigned long	time;

	time = get_time() + milisec;
	while (get_time() < time)
		usleep(100);
}
