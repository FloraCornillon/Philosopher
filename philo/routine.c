/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:00:38 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/17 19:40:22 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	// if (philo->table->nb_of_philo == 1)
	// 	fonction pour gerer un philo
	while (true)
	{
		if (check_if_dead(philo))
			break ;
		if (is_dead(philo) || !ft_think(philo) || !ft_eat(philo) || !ft_sleep(philo))
			break ;
	}
	return (ptr);
}


bool	check_if_dead(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->table->global);
	is_dead = philo->table->dead;
	pthread_mutex_unlock(&philo->table->global);
	return (is_dead);
}




		// printf(BLUE"%zu Philosopher %zu is thinking\n"RST, get_timestamp_ms(), philo->id);
		// printf(GREEN"%zu Philosopher %zu is eating\n"RST, get_timestamp_ms(), philo->id);
		// pthread_mutex_unlock(philo->right_fork);
		// pthread_mutex_unlock(philo->left_fork);
		// printf(MAG"%zu Philosopher %zu is sleeping\n"RST, get_timestamp_ms(), philo->id);