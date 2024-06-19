/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:53:25 by rperrot           #+#    #+#             */
/*   Updated: 2024/04/15 11:53:25 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*recover_args(char **argv, int argc)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->nb_philo = unsigned_atoi(argv[1]);
	args->time_die = unsigned_atoi(argv[2]);
	args->time_eat = unsigned_atoi(argv[3]);
	args->time_sleep = unsigned_atoi(argv[4]);
	if (argc == 6)
		args->nb_lunch = unsigned_atoi(argv[5]);
	else
		args->nb_lunch = 0;
	if (!args->time_sleep || !args->time_eat || !args->nb_philo || \
		!args->time_die || (argc == 6 && !args->nb_lunch))
		return (free(args), NULL);
	return (args);
}
