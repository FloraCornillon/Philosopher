/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:20:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/23 12:15:10 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	print_msg(t_philo *philo, const char *msg, const char *color)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->write_lock);
	time = (get_timestamp_ms() - philo->table->start_simulation);
	printf("%s%zu %02zu %s%s\n", color, time, philo->id, msg, RST);
	pthread_mutex_unlock(&philo->table->write_lock);
}

bool	ft_think(t_philo *philo)
{
	if (is_dead(philo) || check_if_full(philo))
		return (false);
	print_msg(philo, "is thinking", BLUE);
	return (true);
}


bool	ft_sleep(t_philo *philo)
{
	if (is_dead(philo) || check_if_full(philo))
		return (false);
	print_msg(philo, "is sleeping", MAG);
	usleep(philo->table->time_to_sleep);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->global);
	philo->last_meal = get_timestamp_ms();
	pthread_mutex_unlock(&philo->table->global);
	if (is_dead(philo) || check_if_full(philo))
		return (false);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork", "");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork", "");
	print_msg(philo, "is eating", GREEN);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->table->global);
	if (philo->table->nb_of_time_to_eat != -2)
		philo->nb_of_meal++;
	pthread_mutex_unlock(&philo->table->global);
	return (true);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->global);
	if (philo->table->dead)
		return (pthread_mutex_unlock(&philo->table->global), true);
	// size_t time = get_timestamp_ms() - philo->last_meal;
	// printf("Time : %zu\n", time);
	if ((get_timestamp_ms() - philo->last_meal) > philo->table->time_to_die)
	{
		print_msg(philo, "died", YELLOW);
		philo->table->dead = true;
		return (pthread_mutex_unlock(&philo->table->global), true);
	}
	if (philo->table->dead)
		return (pthread_mutex_unlock(&philo->table->global), true);
	return (pthread_mutex_unlock(&philo->table->global), false);
}

