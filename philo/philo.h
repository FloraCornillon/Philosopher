/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:44 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/31 17:05:24 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define COLORS 1

# if (COLORS)
#  define RST "\033[0m"
#  define RED "\033[1;31m"
#  define GREEN "\033[1;32m"
#  define YELLOW "\033[1;33m"
#  define BLUE "\033[1;34m"
#  define MAG "\033[1;35m"
# else
#  define RST ""
#  define RED ""
#  define GREEN ""
#  define YELLOW ""
#  define BLUE ""
#  define MAG ""
# endif

# define EAT GREEN
# define SLEEP MAG
# define THINK BLUE
# define DEAD YELLOW

typedef struct s_fork
{
	bool			available;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_table
{
	ssize_t			nb_of_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			start_simulation;
	ssize_t			nb_of_time_to_eat;
	ssize_t			think_time;
	t_fork			*forks;
	pthread_t		*threads;
	pthread_mutex_t	global;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	bool			dead;
}					t_table;

typedef struct s_philo
{
	size_t			id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	ssize_t			nb_of_meal;
	ssize_t			last_meal;
	ssize_t			nb_of_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			nb_of_time_to_eat;
	ssize_t			think_time;
	t_table			*table;
}					t_philo;

bool				is_positive_num(const char *str);
bool				parse_input(int argc, char **argv);
size_t				ft_strlen(const char *str);
ssize_t				ft_atosst(const char *str, size_t i);
bool				init_table(int argc, char **argv, t_table *table);
void				*philo_routine(void *arg);
t_philo				*init_philo(t_table *table);
bool				init_thread(ssize_t nb_of_philo, t_philo *philo, \
t_table *table);
bool				init_mutexes(t_table *table);
bool				init_all(int argc, char **argv);
int					error_handle(const char *str, int ret);
void				destroy_mutexes_and_free(t_table *table);
void				*ft_calloc(size_t count, size_t size);
ssize_t				get_timestamp_ms(void);
bool				ft_usleep(size_t time, t_philo *philo);
void				print_msg(t_philo *philo, const char *msg, \
const char *color);
bool				ft_sleep(t_philo *philo);
bool				ft_think(t_philo *philo);
bool				ft_eat(t_philo *philo);
bool				is_dead(t_philo *philo);
void				lonely_philo(t_philo *philo);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*philo_routine(void *ptr);
ssize_t				get_think_tm(t_table *table);
bool				take_fork(t_philo *philo);

#endif