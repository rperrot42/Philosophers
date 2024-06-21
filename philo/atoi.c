/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simpleatoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:01:51 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/21 16:54:10 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	unsigned_atoi(char *str)
{
	int			i;
	long int	value;

	i = 0;
	value = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value *= 10;
		value += str[i] - '0';
		if (value > UINT_MAX)
			return (print_error(ERROR_VALUE_ARG), 0);
		i++;
	}
	if (str[i])
		return (print_error(ERROR_VALUE_ARG), 0);
	if (value == 0)
		return (print_error(ERROR_VALUE_NULL), 0);
	return ((unsigned int)value);
}
