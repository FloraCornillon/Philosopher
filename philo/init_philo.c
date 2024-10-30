/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:47:45 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/29 18:27:16 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*alloc_philos(t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * table->nb_of_philo);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo) * table->nb_of_philo);
	return (philo);
}

static void	setup_philo(t_philo *philo, t_table *table)
{
	ssize_t	i;

	i = 0;
	while (i < table->nb_of_philo)
	{
		philo[i].id = i + 1;
		if (i % 2 == 0)
		{
			philo[i].left_fork = &table->forks[i];
			philo[i].right_fork = &table->forks[(i + 1) % table->nb_of_philo];
		}
		else
		{
			philo[i].right_fork = &table->forks[i];
			philo[i].left_fork = &table->forks[(i + 1) % table->nb_of_philo];
		}
		philo[i].table = table;
		philo[i].nb_of_philo = table->nb_of_philo;
		philo[i].time_to_die = table->time_to_die;
		philo[i].time_to_eat = table->time_to_eat;
		philo[i].time_to_sleep = table->time_to_sleep;
		philo[i].nb_of_time_to_eat = table->nb_of_time_to_eat;
		philo[i].think_time = table->think_time;
		i++;
	}
}

t_philo	*init_philo(t_table *table)
{
	t_philo	*philo;

	philo = alloc_philos(table);
	if (!philo)
		return (NULL);
	setup_philo(philo, table);
	return (philo);
}
