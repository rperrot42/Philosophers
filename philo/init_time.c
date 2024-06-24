/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:50:39 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/21 16:54:01 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	long_time;

	gettimeofday(&time, NULL);
	long_time = time.tv_sec * 1000000 + time.tv_usec;
	return (long_time);
}

bool	ft_usleep(unsigned long time_wait, t_info_philo *info_philo)
{
	unsigned long	time_start;
	unsigned long	actual_time;

	time_start = get_time();
	actual_time = get_time();
	while ((actual_time - time_start) / 1000 < time_wait)
	{
		pthread_mutex_lock(info_philo->mutex_philo_finish);
		if (*info_philo->philo_finish == -1 || \
		*info_philo->philo_finish == info_philo->nb_philo)
		{
			pthread_mutex_unlock(info_philo->mutex_philo_finish);
			return (false);
		}
		pthread_mutex_unlock(info_philo->mutex_philo_finish);
		usleep(500);
		actual_time = get_time();
	}
	return (true);
}

long	get_diff_time(long start, long end)
{
	return ((end - start) / 1000);
}
