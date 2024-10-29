/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:00:38 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/28 17:16:35 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->nb_of_philo == 1)
		return (lonely_philo(philo), ptr);
	while (philo->nb_of_time_to_eat != philo->nb_of_meal)
	{
		if (!ft_eat(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
		if (!ft_think(philo))
			break ;
	}
	return (ptr);
}

void	lonely_philo(t_philo *philo)
{
	print_msg(philo, "is thinking", BLUE);
	print_msg(philo, "has taken a fork", "");
	ft_usleep(philo->table->time_to_die, philo);
	print_msg(philo, "is dead", YELLOW);
}


