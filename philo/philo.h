/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:44 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/25 17:44:11 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HPP
# define PHILO_HPP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>

#define RST	   "\033[0m"
#define RED	   "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"

typedef struct s_philo
{
	size_t	id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}	t_philo;

typedef struct s_table
{
	ssize_t	nb_of_philo;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	nb_of_meal;
	pthread_mutex_t	*forks;
}	t_table;

bool	is_positive_num(const char *str);
bool	parse_input(int argc, char **argv);
size_t	ft_strlen(const char *str);
ssize_t	ft_atosst(const char *str, size_t i);
t_table	*init_table(int argc, char **argv);
void	*philo_routine(void *arg);
t_philo	*init_philo(t_table *table);
bool 	init_thread(int nb_of_philo, t_philo *philo);
bool	init_all(int argc, char **argv);
int		error_handle(const char *str, int ret);


#endif