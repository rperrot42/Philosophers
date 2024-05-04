/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:00:10 by rperrot           #+#    #+#             */
/*   Updated: 2024/04/07 12:00:10 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		print_error(ERROR_NUMBERS_ARGS);
	else
	{
		t_args *args = recover_args(argv, argc);
		if (!args)
			return (1);
		printf("%u\n%u\n%u\n%u\n%u\n", args->nb_philo, args->time_die, args->time_eat, args->time_sleep, args->nb_lunch);
		usleep(5000000);
	}
	return (0);
}
