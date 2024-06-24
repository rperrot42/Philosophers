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
# include <sys/time.h>

# define ERROR_NUMBERS_ARGS "The number of arguments is invalid.\n"
# define ERROR_VALUE_ARG "One of the arguments is not a unsigned int.\n"
# define ERROR_VALUE_NULL "One of the arguments is 0\n"
# define DIED "died"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define TAKE_FORK "has taken a fork"
# define THINK "is thinking"

typedef struct s_mutex_bool
{
	bool			value_bool;
	pthread_mutex_t	count_mutex;
}	t_mutex_bool;

typedef struct s_info_args
{
	unsigned int	time_sleep;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	nb_lunch;
}	t_info_args;

typedef struct s_info_philo
{
	t_info_args		*info_args;
	unsigned int	i_philo;
	t_mutex_bool	*fork_left;
	t_mutex_bool	*fork_right;
	pthread_mutex_t	*mutex_philo_finish;
	unsigned int	actual_lunch;
	long			last_lunch;
	int				*philo_finish;
	pthread_mutex_t	*bprintf;
	long			*time_start;
	int				nb_philo;
}	t_info_philo;

typedef struct all_info
{
	t_info_args		info_args;
	unsigned int	nb_philo;
	t_mutex_bool	*all_fork;
	pthread_t		*all_pthread;
	pthread_mutex_t	bprintf;
	pthread_mutex_t	mutex_philo_finish;
	int				philo_finish;
	long			time_start;
	t_info_philo	*tab_info_philo;
}	t_all_info;

size_t			ft_strlen(char *str);
int				print_error(char *msg);
unsigned int	unsigned_atoi(char *str);
int				create_philo(t_all_info *args);
t_all_info		*init_all_info(char **argv, int argc);
void			free_all_info(t_all_info *all_info, int nb_fork_create);
void			modif_mutex_int(int value, t_info_philo *info_philo);
bool			modif_mutex_int_die(pthread_mutex_t *mutex, \
int *pt_value, int nb_philo);
bool			ft_usleep(unsigned long time_wait, t_info_philo *info_philo);
unsigned long	get_time(void);
bool			think_philo(t_info_philo *info_philo);
bool			eat_philo(t_info_philo *info_philo);
long			get_diff_time(long start, long end);
bool			sleep_philo(t_info_philo *info_philo);
void			change_value_mutex(t_mutex_bool *mutex_bool, bool value);
void			printf_info(char *msg, t_info_philo *info_philo);
bool			print_info_error(char *msg, t_info_philo *info_philo);
void			check_fork_true(bool *exit, t_mutex_bool *fork);
#endif