/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:20:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/24 14:54:16 by fcornill         ###   ########.fr       */
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
	if (philo->table->nb_of_philo % 2 != 0)
	{
		if (!ft_usleep(philo->table->time_to_eat / 2, philo)) //peut etr mutex ici
			return (false);
	}
	else if (is_dead(philo))
		return (false);
	return (true);
}


bool	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping", MAG);
	if (!ft_usleep(philo->table->time_to_sleep, philo))
		return (false);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork", "");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork", "");
	print_msg(philo, "is eating", GREEN);
	philo->last_meal = get_timestamp_ms();
	pthread_mutex_lock(&philo->table->global);
	if (philo->table->nb_of_time_to_eat != -2)
		philo->nb_of_meal++;
	pthread_mutex_unlock(&philo->table->global);
	if (!ft_usleep(philo->table->time_to_eat, philo))
		ret = false;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (check_if_full(philo))
		return (false);
	return (ret);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->global);
	if (philo->table->dead)
		return (pthread_mutex_unlock(&philo->table->global), true);
	if (((get_timestamp_ms() - philo->last_meal) > philo->table->time_to_die))
	{
		print_msg(philo, "died", YELLOW);
		philo->table->dead = true;
		return (pthread_mutex_unlock(&philo->table->global), true);
	}
	if (philo->table->dead)
		return (pthread_mutex_unlock(&philo->table->global), true);
	return (pthread_mutex_unlock(&philo->table->global), false);
}

