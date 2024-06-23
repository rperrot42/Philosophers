/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:00:10 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/21 16:50:40 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_all_info	*all_info;

	if (argc != 5 && argc != 6)
		return (print_error(ERROR_NUMBERS_ARGS), 1);
	else
	{
		all_info = init_all_info(argv, argc);
		if (!all_info)
			return (1);
		create_philo(all_info);
		free_all_info(all_info, -1);
	}
	return (0);
}
