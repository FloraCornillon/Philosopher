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

void	*is_dead(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!philo->table->dead)
	{
		pthread_mutex_lock(&philo->table->global);
		if (philo->table->dead)  // vérifier si un philosophe est mort
		{
			pthread_mutex_unlock(&philo->table->global);
			break;
		}
		if ((get_timestamp_ms() - philo->last_meal) > philo->table->time_to_die)
		{
			 print_msg(philo, "is dead");
    		philo->table->dead = true;
    		pthread_mutex_unlock(&philo->table->global);
    		break ;
		}
		pthread_mutex_unlock(&philo->table->global);
		ft_usleep(1);
	}
	return (NULL);
}

void	print_msg(t_philo *philo, const char *msg)
{
	size_t	time;

	time = (get_timestamp_ms() - philo->table->start_simulation);
	printf("%zu %02zu %s\n", time, philo->id, msg);
}

bool	take_fork(t_philo *philo)
{
	if (philo->left_fork == NULL || philo->right_fork == NULL)
		return (false);
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (false);
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	print_msg(philo, "has taken a fork");
	return (true);
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

bool	unlock_fork(t_philo *philo)
{
	if (philo->left_fork == NULL || philo->right_fork == NULL)
		return (false);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (false);
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (false);
	return (true);
}
