/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:01:25 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/22 19:52:24 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	len_str;

	len_str = -1;
	while (str[++len_str])
		;
	return (len_str);
}

int	print_error(char *msg)
{
	return (write(STDERR_FILENO, msg, ft_strlen(msg)));
}

void	printf_info(char *msg, t_info_philo *info_philo)
{
	pthread_mutex_lock(info_philo->bprintf);
	printf("%ld %d %s\n", \
	(get_time() - *info_philo->time_start) / 1000, info_philo->i_philo + 1, \
	msg);
	pthread_mutex_unlock(info_philo->bprintf);
}

bool	print_info_error(char *msg, t_info_philo *info_philo)
{
	pthread_mutex_lock(info_philo->mutex_philo_finish);
	if (*info_philo->philo_finish == -1 || \
	*info_philo->philo_finish == info_philo->nb_philo)
	{
		pthread_mutex_unlock(info_philo->mutex_philo_finish);
		return (false);
	}
	printf_info(msg, info_philo);
	pthread_mutex_unlock(info_philo->mutex_philo_finish);
	return (true);
}
