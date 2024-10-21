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
	if (philo->table->nb_of_philo == 1)
	{
		lonely_philo(philo);
		return (ptr);
	}
	while (true)
	{
		if (check_if_dead(philo) || check_if_full(philo))
			break ;
		if (is_dead(philo) || !ft_think(philo) || !ft_eat(philo) || !ft_sleep(philo))
			break ;
	}
	return (ptr);
}


bool	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->global);
	if (philo->table->dead == true)
		return (pthread_mutex_unlock(&philo->table->global), true);
	return (pthread_mutex_unlock(&philo->table->global), false);
}

bool	check_if_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->global);
	if (philo->nb_of_meal == philo->table->nb_of_time_to_eat)
		return(pthread_mutex_unlock(&philo->table->global), true);
	return (pthread_mutex_unlock(&philo->table->global), false);
}

void	lonely_philo(t_philo *philo)
{
	print_msg(philo, "is thinking", BLUE);
	print_msg(philo, "has taken a fork", "");
	print_msg(philo, "is dead", YELLOW);
	// philo->table->dead = true;
	// ft_usleep(philo->table->time_to_die);
}
