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
	if (print_info_error(THINK, info_philo) == false)
		return (false);
	if (wait_fork(info_philo, info_philo->fork_left) == true)
		return (false);
	if (wait_fork(info_philo, info_philo->fork_right) == true)
		return (false);
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
		usleep(500);
		check_fork_true(&exit, fork);
		pthread_mutex_lock(info_philo->mutex_philo_finish);
		if (*info_philo->philo_finish == -1 || \
		*info_philo->philo_finish == info_philo->nb_philo)
			error = true;
		pthread_mutex_unlock(info_philo->mutex_philo_finish);
		if ((get_time() - info_philo->last_lunch) / 1000 > \
		info_philo->info_args->time_die)
			return (modif_mutex_int(-1, info_philo), true);
	}
	if (error == false)
		if (print_info_error(TAKE_FORK, info_philo) == false)
			return (false);
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
	if (print_info_error(EAT, info_philo) == false)
		return (false);
	if (ft_usleep(time_eat, info_philo) == false)
		return (false);
	if (die_philo == true)
		return (modif_mutex_int(-1, info_philo), false);
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
	if (print_info_error(SLEEP, info_philo) == false)
		return (false);
	if (ft_usleep(time_sleep, info_philo) == false)
		return (false);
	if (die_philo == true)
		return (modif_mutex_int(-1, info_philo), false);
	return (true);
}
