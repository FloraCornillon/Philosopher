/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:20:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/17 19:50:53 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	print_msg(t_philo *philo, const char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->table->write_lock);
	time = (get_timestamp_ms() - philo->table->start_simulation);
	printf("%zu %02zu %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->table->write_lock);
}

void	ft_think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}


void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

