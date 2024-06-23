/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperrot <rperrot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:53:25 by rperrot           #+#    #+#             */
/*   Updated: 2024/06/21 16:54:28 by rperrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	create_all_forks(t_all_info *all_info);

static bool	create_all_philo_info(t_all_info *all_info);

static bool	recover_args(char **argv, int argc, t_all_info *all_info)
{
	all_info->nb_philo = unsigned_atoi(argv[1]);
	all_info->info_args.time_die = unsigned_atoi(argv[2]);
	all_info->info_args.time_eat = unsigned_atoi(argv[3]);
	all_info->info_args.time_sleep = unsigned_atoi(argv[4]);
	if (argc == 6)
		all_info->info_args.nb_lunch = unsigned_atoi(argv[5]);
	else
		all_info->info_args.nb_lunch = 0;
	if (!all_info->info_args.time_sleep || !all_info->info_args.time_eat || \
	!all_info->nb_philo || !all_info->info_args.time_die || \
	(argc == 6 && !all_info->info_args.nb_lunch))
		return (false);
	return (true);
}

t_all_info	*init_all_info(char **argv, int argc)
{
	t_all_info		*all_info;

	all_info = malloc(sizeof(t_all_info));
	if (!all_info)
		return (NULL);
	*all_info = (t_all_info){0};
	if (recover_args(argv, argc, all_info) == false)
		return (free(all_info), NULL);
	if (pthread_mutex_init(&all_info->philo_die.count_mutex, NULL))
		return (free(all_info), NULL);
	if (pthread_mutex_init(&all_info->bprintf, NULL))
		return (free(all_info), \
		pthread_mutex_destroy(&all_info->bprintf), NULL);
	if (create_all_forks(all_info) == false)
		return (NULL);
	all_info->all_pthread = malloc(sizeof(pthread_t) * all_info->nb_philo);
	if (!all_info->all_pthread)
		return (free_all_info(all_info, -1), NULL);
	if (create_all_philo_info(all_info) == false)
		return (NULL);
	return (all_info);
}

static bool	create_all_forks(t_all_info *all_info)
{
	unsigned int	i;

	all_info->all_fork = malloc(sizeof(t_mutex_bool) * all_info->nb_philo);
	if (!all_info->all_fork)
		return (free_all_info(all_info, -1), false);
	i = -1;
	while (++i < all_info->nb_philo)
	{
		all_info->all_fork[i].value_bool = false;
		if (pthread_mutex_init(&all_info->all_fork[i].count_mutex, NULL))
			return ((free_all_info(all_info, (int)i + 1), false));
	}
	return (true);
}

void	free_all_info(t_all_info *all_info, int nb_fork_create)
{
	int	i;

	if (nb_fork_create == -1)
		nb_fork_create = (int)all_info->nb_philo;
	if (all_info->all_fork)
	{
		i = -1;
		while (++i < nb_fork_create)
			pthread_mutex_destroy(&all_info->all_fork[i].count_mutex);
		free(all_info->all_fork);
	}
	if (all_info->all_pthread)
		free(all_info->all_pthread);
	if (all_info->tab_info_philo)
		free(all_info->tab_info_philo);
	pthread_mutex_destroy(&all_info->philo_die.count_mutex);
	pthread_mutex_destroy(&all_info->bprintf);
	free(all_info);
}

static bool	create_all_philo_info(t_all_info *all_info)
{
	unsigned int	i;

	all_info->tab_info_philo = \
	malloc(sizeof(t_info_philo) * all_info->nb_philo);
	if (!all_info->tab_info_philo)
		return (free_all_info(all_info, -1), false);
	i = -1;
	while (++i < all_info->nb_philo)
	{
		all_info->tab_info_philo[i] = (t_info_philo){0};
		all_info->tab_info_philo[i].bprintf = &all_info->bprintf;
		all_info->tab_info_philo[i].i_philo = i;
		all_info->tab_info_philo[i].info_args = &all_info->info_args;
		all_info->tab_info_philo[i].philo_die = &all_info->philo_die;
		all_info->tab_info_philo[i].fork_left = &all_info->all_fork[i];
		all_info->tab_info_philo[i].fork_right = \
		&all_info->all_fork[(i + 1) % all_info->nb_philo];
		all_info->tab_info_philo[i].time_start = &all_info->time_start;
	}
	return (true);
}
