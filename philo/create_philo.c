/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:48:22 by rperrot           #+#    #+#             */
/*   Updated: 2024/04/15 14:48:27 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	printf("je suis le philo %d\n", *((int *)data));
	return (NULL);
}

int create_philo(t_args *args)
{
	unsigned int i;
	unsigned int *list_i;

	list_i = malloc(args->nb_philo * (sizeof(unsigned  int )));
	pthread_t	*list_tid;

	i = 0;
	list_tid = malloc(args->nb_philo * (sizeof(pthread_t)));
	if (!list_tid)
		return (1);
	while (i < args->nb_philo)
	{
		list_i[i] = i;
		pthread_create(&list_tid[i], NULL, thread_routine, &list_i[i]);
		i += 2;
	}
	i = 1;
	usleep(100);
	while (i < args->nb_philo)
	{
		list_i[i] = i;
		pthread_create(&list_tid[i], NULL, thread_routine, &list_i[i]);
		i += 2;
	}
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(list_tid[i], NULL);
	return (0);
}
