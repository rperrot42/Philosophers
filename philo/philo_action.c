/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:38:18 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/22 10:38:23 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	wait_fork(t_info_philo *info_philo, t_mutex_bool *fork);

bool	think_philo(t_info_philo *info_philo)
{
	pthread_mutex_lock(info_philo->bprintf);
	printf("%ld %d is thinking\n", (get_time() - *info_philo->time_start) / 1000, info_philo->i_philo);
	pthread_mutex_unlock(info_philo->bprintf);
	if (info_philo->i_philo % 2)
	{
		if (wait_fork(info_philo, info_philo->fork_left) == true)
			return (false);
		if (wait_fork(info_philo, info_philo->fork_right) == true)
			return (false);
	}
	else
	{
		if (wait_fork(info_philo, info_philo->fork_left) == true)
			return (false);
		if (wait_fork(info_philo, info_philo->fork_right) == true)
			return (false);
	}
	return (true);
}

bool	wait_fork(t_info_philo *info_philo, t_mutex_bool *fork)
{
	bool	exit;
	bool	error;

	exit = false;
	error = false;
	while (exit == false && error == false)
	{
		usleep(42);
		pthread_mutex_lock(&fork->count_mutex);
		if (fork->value_bool == false)
		{
			fork->value_bool = true;
			exit = true;
		}
		pthread_mutex_unlock(&fork->count_mutex);
		pthread_mutex_lock(&info_philo->philo_die->count_mutex);
		if (info_philo->philo_die->value_bool == true)
			error = true;
		pthread_mutex_unlock(&info_philo->philo_die->count_mutex);
		if ((get_time() - info_philo->last_lunch) / 1000 > info_philo->info_args->time_die)
		{
			error = true;
			pthread_mutex_lock(&info_philo->philo_die->count_mutex);
			if (info_philo->philo_die->value_bool == true)
				info_philo->philo_die->value_bool = true;
			pthread_mutex_unlock(&info_philo->philo_die->count_mutex);
		}
	}
	if (error == false)
		printf("%ld %d has taken a fork\n", (get_time() - *info_philo->time_start) / 1000, info_philo->i_philo);
	return (error);
}

bool	eat_philo(t_info_philo *info_philo, t_mutex_bool *fork)
{
	info_philo-
}
