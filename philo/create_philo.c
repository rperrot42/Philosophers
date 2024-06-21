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

void	*thread_routine(void *data)
{
	printf("je suis le philo %d\n", ((t_info_philo *)data)->i_philo);
	return (NULL);
}

int create_philo(t_all_info *args)
{
	unsigned int i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_create(&args->all_pthread[i], NULL, thread_routine, &args->tab_info_philo[i]);
		i += 2;
	}
	i = 1;
	usleep(10000);
	while (i < args->nb_philo)
	{
		pthread_create(&args->all_pthread[i], NULL, thread_routine, &args->tab_info_philo[i]);
		i += 2;
	}
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->all_pthread[i], NULL);
	return (0);
}
