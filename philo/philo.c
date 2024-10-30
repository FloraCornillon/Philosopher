/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:20:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/29 17:53:34 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->global);
	if (!philo->left_fork->available || !philo->right_fork->available)
		return (pthread_mutex_unlock(&philo->table->global), false);
	philo->left_fork->available = false;
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->right_fork->available = false;
	pthread_mutex_lock(&philo->right_fork->mutex);
	return (pthread_mutex_unlock(&philo->table->global), true);
}

bool	ft_think(t_philo *philo)
{
	bool	ret;

	ret = true;
	if (is_dead(philo))
		return (false);
	print_msg(philo, "is thinking", BLUE);
	ft_usleep(philo->think_time);
	while (!take_fork(philo))
	{
		usleep(100);
		if (is_dead(philo))
		{
			ret = false;
			break ;
		}
	}
	print_msg(philo, "has taken a fork", "");
	return (ret);
}

bool	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping", MAG);
	ft_usleep(philo->time_to_sleep);
	if (is_dead(philo))
		return (false);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	philo->last_meal = get_timestamp_ms();
	print_msg(philo, "is eating", GREEN);
	if (philo->nb_of_time_to_eat != -2)
		philo->nb_of_meal++;
	ft_usleep(philo->time_to_eat);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (false);
	}
	pthread_mutex_lock(&philo->table->global);
	philo->left_fork->available = true;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	philo->right_fork->available = true;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->table->global);
	return (true);
}
