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

	pthread_mutex_lock(&philo->table->write_lock);
	time = (get_timestamp_ms() - philo->table->start_simulation);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%zu %02zu %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->table->write_lock);
}

bool	ft_think(t_philo *philo)
{
	if (check_if_dead(philo) || check_if_full(philo))
		return (false);
	print_msg(philo, "is thinking");
	return (true);
}


bool	ft_sleep(t_philo *philo)
{
	if (check_if_dead(philo) || check_if_full(philo))
		return (false);
	print_msg(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	if (check_if_dead(philo) || check_if_full(philo))
		return (false);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->last_meal = get_timestamp_ms();
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->table->nb_of_time_to_eat != -2)
		philo->nb_of_meal++;
	return (true);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->global);
	if ((get_timestamp_ms() - philo->last_meal) > philo->table->time_to_die)
	{
		print_msg(philo, "is dead");
		philo->table->dead = true;
		return (pthread_mutex_unlock(&philo->table->global), true);
	}
	return (pthread_mutex_unlock(&philo->table->global), false);
}

