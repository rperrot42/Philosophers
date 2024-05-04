/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:00:02 by rperrot           #+#    #+#             */
/*   Updated: 2024/04/07 12:00:02 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

# define ERROR_NUMBERS_ARGS "The number of arguments is invalid.\n"
# define ERROR_VALUE_ARG "One of the arguments is not a unsigned int.\n"
# define ERROR_VALUE_NULL "One of the arguments is 0\n"

typedef struct s_args
{
	unsigned int	time_sleep;
	unsigned int	time_eat;
	unsigned int	nb_philo;
	unsigned int	nb_lunch;
	unsigned int	time_die;
}	t_args;

size_t		ft_strlen(char *str);
int			print_error(char *msg);
unsigned int unsigned_atoi(char *str);
t_args	*recover_args(char **argv, int argc);

#endif