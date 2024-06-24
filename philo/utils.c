/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:58:16 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/22 19:58:16 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_value_mutex(t_mutex_bool *mutex_bool, bool value)
{
	pthread_mutex_lock(&mutex_bool->count_mutex);
	mutex_bool->value_bool = value;
	pthread_mutex_unlock(&mutex_bool->count_mutex);
}

void	modif_mutex_int(int value, t_info_philo *info_philo)
{
	pthread_mutex_lock(info_philo->mutex_philo_finish);
	if (*info_philo->philo_finish != -1)
	{
		*info_philo->philo_finish = value;
		if (value == -1)
			printf_info(DIED, info_philo);
	}
	pthread_mutex_unlock(info_philo->mutex_philo_finish);
}

bool	modif_mutex_int_die(pthread_mutex_t *mutex, int *pt_value, int nb_philo)
{
	pthread_mutex_lock(mutex);
	if (*pt_value == -1)
	{
		pthread_mutex_unlock(mutex);
		return (false);
	}
	*pt_value = *pt_value + 1;
	if (*pt_value == nb_philo)
	{
		pthread_mutex_unlock(mutex);
		return (false);
	}
	pthread_mutex_unlock(mutex);
	return (true);
}

void	check_fork_true(bool *exit, t_mutex_bool *fork)
{
	pthread_mutex_lock(&fork->count_mutex);
	if (fork->value_bool == false)
	{
		fork->value_bool = true;
		*exit = true;
	}
	pthread_mutex_unlock(&fork->count_mutex);
}
