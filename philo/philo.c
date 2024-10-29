/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:20:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/29 17:31:10 by fcornill         ###   ########.fr       */
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
	ft_usleep(philo->think_time, philo);
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
	ft_usleep(philo->time_to_sleep, philo);
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
	ft_usleep(philo->time_to_eat, philo);
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




