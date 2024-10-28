/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:44:15 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/28 17:31:24 by fcornill         ###   ########.fr       */
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
	return (true);
}

bool	init_mutexes(t_table *table)
{
	ssize_t	i;

	i = 0;
	table->forks = malloc(sizeof(t_fork) * table->nb_of_philo);
	if (!table->forks)
		return (false);
	memset(table->forks, 0, sizeof(t_fork) * table->nb_of_philo);
	while (i < table->nb_of_philo)
	{
		table->forks[i].available = true;
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
		{
			printf(RED"Failed to init mutex %zu\n"RST, i);
			return (false);
		}
		i++;
	}
	if (pthread_mutex_init(&table->global, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
		return (false);
	return (true);
}


t_philo	*init_philo(t_table *table)
{
	ssize_t	i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->nb_of_philo);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo) * table->nb_of_philo);
	while (i < table->nb_of_philo)
	{
		philo[i].id = i + 1;
		// if (i % 2 == 0)
		// {
		// 	philo[i].left_fork = &table->forks[i];
		// 	philo[i].right_fork = &table->forks[(i + 1) % table->nb_of_philo];
		// }
		// else
		// {
		// 	philo[i].right_fork = &table->forks[i];
		// 	philo[i].left_fork = &table->forks[(i + 1) % table->nb_of_philo];
		// }
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = &table->forks[(i + 1) % table->nb_of_philo];
		philo[i].table = table;
		philo[i].last_meal = get_timestamp_ms();
		philo[i].nb_of_philo = table->nb_of_philo;
		philo[i].time_to_die = table->time_to_die;
		philo[i].time_to_eat = table->time_to_eat;
		philo[i].time_to_sleep = table->time_to_sleep;
		philo[i].nb_of_time_to_eat = table->nb_of_time_to_eat;
		i++;
	}
	return (philo);
}

bool 	init_thread(ssize_t nb_of_philo, t_philo *philo)
{
	pthread_t	threads[nb_of_philo];
	ssize_t	i;

	i = -1;
	while (++i < nb_of_philo)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &philo[i]) != 0)
		{
			printf(RED"Failed to create thread %zu\n"RST, i);
			return (false);
		}
	}
	i = -1;
	while (++i < nb_of_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf(RED"Failed to join thread %zu\n"RST, i);
			return (false);
		}
	}
	return (true);
}

bool	init_all(int argc, char **argv)
{
	t_table		table;
	t_philo		*philo;

	if (!init_table(argc, argv, &table))
		return (false);
	if (!init_mutexes(&table))
		return (false);
	philo = init_philo(&table);
	if (!philo)
	{
		destroy_mutexes(&table);
		return (false);
	}
	if (!init_thread(table.nb_of_philo, philo))
	{
		destroy_mutexes(&table);
		free(philo);
		return (false);
	}
	destroy_mutexes(&table);
	free(philo);
	return (true);
}
