/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:39:32 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/31 17:06:34 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, const char *msg, const char *color)
{
	size_t		time;
	static bool	print = true;

	pthread_mutex_lock(&philo->table->write_lock);
	time = (get_timestamp_ms() - philo->table->start_simulation);
	if (print)
		printf("%s%zu %02zu %s%s\n", color, time, philo->id, msg, RST);
	if (!ft_strncmp(msg, "died", 4))
		print = false;
	pthread_mutex_unlock(&philo->table->write_lock);
}

ssize_t	get_timestamp_ms(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		printf(RED"Gettimeofday failed\n"RST);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

bool	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_timestamp_ms();
	while (get_timestamp_ms() - start < time)
	{
		if (is_dead(philo))
			return (false);
		usleep(500);
	}
	return (true);
}

ssize_t	get_think_tm(t_table *table)
{
	ssize_t	think_time;

	think_time = 3 * table->time_to_eat / 2;
	if (table->nb_of_philo % 2 == 0 || think_time <= table->time_to_sleep)
		return (0);
	return (think_time - table->time_to_sleep);
}
