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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->global);
	philo->last_meal = get_timestamp_ms();
	pthread_mutex_unlock(&philo->table->global);
	pthread_create(&philo->supervisor, NULL, &supervisor_routine, philo);
	pthread_detach(philo->supervisor);
	if (philo->id % 2 == 0)
		ft_usleep(1);
	// if (philo->table->nb_of_philo == 1)
	// 	fonction pour gerer un philo
	while (philo->nb_of_meal < philo->table->nb_of_time_to_eat)
	{
		pthread_mutex_lock(&philo->table->global);
		if (philo->table->dead)
		{
			pthread_mutex_unlock(&philo->table->global);
			break;
		}
    	pthread_mutex_unlock(&philo->table->global);
    	print_msg(philo, "is thinking");
    	if (!take_fork(philo))
        	break;
    	print_msg(philo, "is eating");
    	pthread_mutex_lock(&philo->table->global);
    	philo->last_meal = get_timestamp_ms();
   	 	philo->nb_of_meal++;
   		pthread_mutex_unlock(&philo->table->global);
		ft_usleep(philo->table->time_to_eat);
		if (!unlock_fork(philo))
			break ;
	}
	return (NULL);
}

void	*supervisor_routine(void *arg)
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





		// printf(BLUE"%zu Philosopher %zu is thinking\n"RST, get_timestamp_ms(), philo->id);
		// printf(GREEN"%zu Philosopher %zu is eating\n"RST, get_timestamp_ms(), philo->id);
		// pthread_mutex_unlock(philo->right_fork);
		// pthread_mutex_unlock(philo->left_fork);
		// printf(MAG"%zu Philosopher %zu is sleeping\n"RST, get_timestamp_ms(), philo->id);