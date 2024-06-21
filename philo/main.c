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
	t_args	*args;

	if (argc != 5 && argc != 6)
		print_error(ERROR_NUMBERS_ARGS);
	else
	{
		args = recover_args(argv, argc);
		if (!args)
			return (1);
		create_philo(args);
	}
	return (0);
}
