/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:44:15 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/25 17:04:46 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->nb_of_philo = ft_atosst(argv[1], 1);
	table->time_to_die = ft_atosst(argv[2], 2);
	table->time_to_eat = ft_atosst(argv[3], 3);
	table->time_to_sleep = ft_atosst(argv[4], 4);
	if (argc == 6)
		table->nb_of_meal = ft_atosst(argv[5], 5);
	if (table->nb_of_philo == -1 || table->time_to_die == -1 || table->time_to_eat == -1 \
|| table->time_to_sleep == -1 || table->nb_of_meal == -1)
	{
		free(table);
		return (NULL);
	}
	return (table);
}


t_philo	*init_philo(t_table *table)
{
	t_philo	*philo;
	ssize_t	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->nb_of_philo);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo) * table->nb_of_philo);
	while (i < table->nb_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = &table->forks[(i + 1) % table->nb_of_philo];
		i++;
	}
	return (philo);
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
	t_table		*table;
	t_philo		*philo;

	table = init_table(argc, argv);
	if (!table)
		return (false);
	philo = init_philo(table);
	if (!philo)
	{
		free(table);
		return (false);
	}
	if (!init_thread(table->nb_of_philo, philo))
	{
		free(table);
		free(philo);
		return (false);
	}
	return (true);
}
