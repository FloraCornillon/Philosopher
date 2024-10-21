/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:44 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/17 19:12:07 by fcornill         ###   ########.fr       */
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
#define BLUE   "\033[1;34m"
#define MAG    "\033[1;35m"

typedef struct s_table
{
	ssize_t	nb_of_philo;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	start_simulation;
	ssize_t	nb_of_time_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t global;
	pthread_mutex_t write_lock;
	bool	dead;
}	t_table;

typedef struct s_philo
{
	size_t	id;
	ssize_t	nb_of_meal;
	ssize_t	last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_t	supervisor;
	t_table	*table;
}	t_philo;



bool	is_positive_num(const char *str);
bool	parse_input(int argc, char **argv);
size_t	ft_strlen(const char *str);
ssize_t	ft_atosst(const char *str, size_t i);
bool	init_table(int argc, char **argv, t_table *table);
void	*philo_routine(void *arg);
t_philo	*init_philo(t_table *table);
bool 	init_thread(ssize_t nb_of_philo, t_philo *philo);
bool	init_mutexes(t_table *table);
bool	init_all(int argc, char **argv);
int		error_handle(const char *str, int ret);
void	destroy_mutexes(t_table *table);
ssize_t	get_timestamp_ms(void);
void	ft_usleep(size_t time);
void	*supervisor_routine(void *arg);
void	print_msg(t_philo *philo, const char *msg);
bool	ft_sleep(t_philo *philo);
bool	ft_think(t_philo *philo);
bool	ft_eat(t_philo *philo);
bool	is_dead(t_philo *philo);
bool	check_if_dead(t_philo *philo);


#endif