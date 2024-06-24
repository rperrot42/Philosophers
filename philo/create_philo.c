/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:48:22 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/21 16:52:47 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_start(t_info_philo	*info_philo)
{
	bool			exit;

	exit = false;
	while (exit == false)
	{
		usleep(100);
		pthread_mutex_lock(info_philo->bprintf);
		if (*info_philo->time_start)
			exit = true;
		pthread_mutex_unlock(info_philo->bprintf);
	}
}

void	*thread_routine(void *data)
{
	t_info_philo	*info_philo;
	bool			exit;

	info_philo = (t_info_philo *)data;
	wait_start(info_philo);
	info_philo->last_lunch = *info_philo->time_start;
	if (info_philo->i_philo % 2 == 1)
		usleep(10000);
	exit = false;
	while (exit == false)
	{
		if (think_philo(info_philo) == false)
			exit = true;
		if (exit == false && eat_philo(info_philo) == false)
			exit = true;
		info_philo->actual_lunch++;
		if (exit == false && info_philo->actual_lunch == info_philo->info_args->\
nb_lunch && modif_mutex_int_die(info_philo->mutex_philo_finish, \
info_philo->philo_finish, 0) == false)
			exit = true;
		if (exit == false && sleep_philo(info_philo) == false)
			exit = true;
	}
	return (NULL);
}

int	create_philo(t_all_info *args)
{
	unsigned int	i;

	i = -1;
	while (++i < args->nb_philo)
		pthread_create(&args->all_pthread[i], NULL, \
thread_routine, &args->tab_info_philo[i]);
	pthread_mutex_lock(&args->bprintf);
	args->time_start = get_time();
	pthread_mutex_unlock(&args->bprintf);
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->all_pthread[i], NULL);
	return (0);
}
