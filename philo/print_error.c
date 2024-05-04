/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:01:25 by rperrot           #+#    #+#             */
/*   Updated: 2024/04/15 11:01:25 by rperrot          ###   ########.fr       */
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
