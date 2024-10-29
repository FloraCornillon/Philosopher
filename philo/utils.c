/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:17:04 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/29 17:32:20 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


int	error_handle(const char *str, int ret)
{
	printf(RED"%s"RST, str);
	return (ret);
}

void	destroy_mutexes(t_table *table)
{
	ssize_t	i;

	i = 0;
	while (i < table->nb_of_philo)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&table->global);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->dead_lock);
	free(table->forks);
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
	(void)philo;
	while (get_timestamp_ms() - start < time)
		usleep(500);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}
