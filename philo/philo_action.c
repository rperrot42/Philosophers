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
	printf_info("is thinking", info_philo);
	if (info_philo->i_philo % 2)
	{
		if (wait_fork(info_philo, info_philo->fork_left) == true)
			return (false);
		if (wait_fork(info_philo, info_philo->fork_right) == true)
			return (false);
	}
	else
	{
		if (wait_fork(info_philo, info_philo->fork_right) == true)
			return (false);
		if (wait_fork(info_philo, info_philo->fork_left) == true)
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
		check_fork_true(&exit, fork);
		pthread_mutex_lock(&info_philo->philo_die->count_mutex);
		if (info_philo->philo_die->value_bool == true)
			error = true;
		pthread_mutex_unlock(&info_philo->philo_die->count_mutex);
		if ((get_time() - info_philo->last_lunch) / 1000 > \
		info_philo->info_args->time_die)
		{
			error = true;
			change_value_mutex(info_philo->philo_die, true);
		}
	}
	if (error == false)
		printf_info("is taken a fork", info_philo);
	return (error);
}

bool	eat_philo(t_info_philo *info_philo)
{
	unsigned int	time_eat;
	bool			die_philo;

	die_philo = false;
	if (info_philo->info_args->time_die < info_philo->info_args->time_eat)
	{
		time_eat = info_philo->info_args->time_die;
		die_philo = true;
	}
	else
		time_eat = info_philo->info_args->time_eat;
	info_philo->last_lunch = get_time();
	printf_info("eating", info_philo);
	if (ft_usleep(time_eat, info_philo->philo_die) == false)
		return (false);
	if (die_philo == true)
		return (change_value_mutex(info_philo->philo_die, true), false);
	change_value_mutex(info_philo->fork_right, false);
	change_value_mutex(info_philo->fork_left, false);
	return (true);
}

bool	sleep_philo(t_info_philo *info_philo)
{
	unsigned int	time_sleep;
	bool			die_philo;

	die_philo = false;
	if (info_philo->info_args->time_die < info_philo->info_args->time_sleep + \
get_diff_time(info_philo->last_lunch, get_time()))
	{
		time_sleep = info_philo->info_args->time_die;
		die_philo = true;
	}
	else
		time_sleep = info_philo->info_args->time_eat;
	printf_info("sleeping", info_philo);
	if (ft_usleep(time_sleep, info_philo->philo_die) == false)
		return (false);
	if (die_philo == true)
		return (change_value_mutex(info_philo->philo_die, true), false);
	return (true);
}
