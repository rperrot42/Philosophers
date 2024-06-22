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
