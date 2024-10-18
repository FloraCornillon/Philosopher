/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:44:15 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/17 19:45:56 by fcornill         ###   ########.fr       */
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
	table->start_simulation = get_timestamp_ms();
	table->dead = false;
	if (argc == 6)
		table->nb_of_time_to_eat = ft_atosst(argv[5], 5);
	else
		table->nb_of_time_to_eat = -2;
	if (table->nb_of_philo == -1 || table->time_to_die == -1 || table->time_to_eat == -1 \
|| table->time_to_sleep == -1 || table->nb_of_time_to_eat == -1)
		return (false);
	return (table);
}

bool	init_mutexes(t_table *table)
{
	ssize_t	i;

	i = 0;
	memset(table->forks, 0, sizeof(pthread_mutex_t) * table->nb_of_philo);
	while (i < table->nb_of_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf(RED"Failed to init mutex %zu\n"RST, i);
			return (false);
		}
		i++;
	}
	if (pthread_mutex_init(&table->global, NULL) != 0)
		return (false);
	return (true);
}


bool	init_philo(t_table *table, t_philo *philo)
{
	ssize_t	i;

	i = 0;
	if (!philo)
		return (false);
	memset(philo, 0, sizeof(t_philo) * table->nb_of_philo);
	while (i < table->nb_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = &table->forks[(i + 1) % table->nb_of_philo];
		philo[i].table = table;
		i++;
	}
	return (true);
}

bool 	init_thread(int nb_of_philo, t_philo *philo)
{
	pthread_t	threads[nb_of_philo];
	
	ssize_t	i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &philo[i]) != 0)
		{
			printf(RED"Failed to create thread %zu\n"RST, i);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf(RED"Failed to join thread %zu\n"RST, i);
			return (false);
		}
		i++;
	}
	return (true);
}



bool	init_all(int argc, char **argv)
{
	t_table		table;
	t_philo		philo;

	if (!init_table(argc, argv, &table));
		return (false);
	if (!init_mutexes(&table))
		return (false);
	if (!init_philo(&table, &philo))
	{
		destroy_mutexes(&table);
		return (false);
	}
	if (!init_thread(&table.nb_of_philo, &philo))
	{
		destroy_mutexes(&table);
		return (false);
	}
	destroy_mutexes(&table);
	return (true);
}
