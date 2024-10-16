/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:00:38 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/16 16:45:16 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// philo->last_meal = get_timestamp_ms();
	// printf("%zd time\n", philo->last_meal);
	while (philo->nb_of_meal < philo->table->nb_of_time_to_eat)
	{
		//if (is_dead(philo))
		//	printf, break
		printf(BLUE"%zu Philosopher %zu is thinking\n"RST, get_timestamp_ms(), philo->id);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		printf(GREEN"%zu Philosopher %zu is eating\n"RST, get_timestamp_ms(), philo->id);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf(MAG"%zu Philosopher %zu is sleeping\n"RST, get_timestamp_ms(), philo->id);
	}
	return (NULL);
}