/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:17:04 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/17 18:38:46 by fcornill         ###   ########.fr       */
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
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

ssize_t	get_timestamp_ms(void)
{
	struct timeval	now;
	
	if (gettimeofday(&now, NULL) == -1)
		printf(RED"Gettimeofday failed\n"RST);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	ft_usleep(size_t time)
{
	usleep(time * 1000);
}
