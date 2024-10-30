/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:44:15 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/29 18:26:09 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_table(int argc, char **argv, t_table *table)
{
	if (!table)
		return (false);
	memset(table, 0, sizeof(t_table));
	table->nb_of_philo = ft_atosst(argv[1], 1);
	table->time_to_die = ft_atosst(argv[2], 2);
	table->time_to_eat = ft_atosst(argv[3], 3);
	table->time_to_sleep = ft_atosst(argv[4], 4);
	if (table->nb_of_philo == -1 || table->time_to_die == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1
		|| table->nb_of_time_to_eat == -1)
		return (false);
	table->start_simulation = get_timestamp_ms();
	table->think_time = get_think_tm(table);
	table->dead = false;
	if (argc == 6)
		table->nb_of_time_to_eat = ft_atosst(argv[5], 5);
	else
		table->nb_of_time_to_eat = -2;
	table->threads = ft_calloc(table->nb_of_philo, sizeof(pthread_t));
	if (!table->threads)
		return (false);
	return (true);
}

bool	init_mutexes(t_table *table)
{
	ssize_t	i;

	i = 0;
	table->forks = ft_calloc(table->nb_of_philo, sizeof(t_fork));
	if (!table->forks)
		return (false);
	while (i < table->nb_of_philo)
	{
		table->forks[i].available = true;
		if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0)
		{
			printf(RED "Failed to init mutex %zu\n" RST, i);
			while (--i >= 0)
                pthread_mutex_destroy(&table->forks[i].mutex);
            return (free(table->forks), free(table->threads), false);
		}
		i++;
	}
	if (pthread_mutex_init(&table->global, NULL) != 0 || \
        pthread_mutex_init(&table->write_lock, NULL) != 0 || \
        pthread_mutex_init(&table->dead_lock, NULL) != 0)
        	destroy_mutexes_and_free(table); 
	return (true);
}

bool	init_thread(ssize_t nb_of_philo, t_philo *philo, t_table *table)
{
	ssize_t		i;

	i = -1;
	while (++i < nb_of_philo)
	{
		philo[i].last_meal = table->start_simulation;
		if (pthread_create(&table->threads[i], NULL, philo_routine, &philo[i]) \
	!= 0)
		{
			printf(RED "Failed to create thread %zu\n" RST, i);
			return (false);
		}
	}
	i = -1;
	while (++i < nb_of_philo)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
		{
			printf(RED "Failed to join thread %zu\n" RST, i);
			return (false);
		}
	}
	return (true);
}
