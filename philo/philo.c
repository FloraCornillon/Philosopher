/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:20:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/28 17:37:39 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	print_msg(t_philo *philo, const char *msg, const char *color)
{
	size_t	time;
	static bool	print = true;

	pthread_mutex_lock(&philo->table->write_lock);
	time = (get_timestamp_ms() - philo->table->start_simulation);
	if (print)
		printf("%s%zu %02zu %s%s\n", color, time, philo->id, msg, RST);
	if (!ft_strncmp(msg, "died", 4))
		print = false;
	pthread_mutex_unlock(&philo->table->write_lock);
}


bool	ft_think(t_philo *philo)
{
	print_msg(philo, "is thinking", BLUE);
	if (is_dead(philo))
		return (false);
	return (true);
}


bool	ft_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return (false);
	print_msg(philo, "is sleeping", MAG);
	ft_usleep(philo->time_to_sleep, philo);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork", "");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork", "");
	print_msg(philo, "is eating", GREEN);
	// pthread_mutex_lock(&philo->table->global);
	philo->last_meal = get_timestamp_ms();
	if (philo->nb_of_time_to_eat != -2)
		philo->nb_of_meal++;
	// pthread_mutex_unlock(&philo->table->global);
	ft_usleep(philo->time_to_eat, philo);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}


bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return true;
	}
	if ((get_timestamp_ms() - philo->last_meal) >= philo->time_to_die)
	{
		print_msg(philo, "died", YELLOW);
	 	philo->table->dead = true;
	 	pthread_mutex_unlock(&philo->table->dead_lock);
	 	return true;
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return false;
}

