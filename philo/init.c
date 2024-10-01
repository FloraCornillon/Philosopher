/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:44:15 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/25 17:04:46 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*Init_table(int argc, char **argv)
{
	t_table	*table;
	
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->nb_of_philo = ft_atosst(argv[1], 1);
	table->time_to_die = ft_atosst(argv[2], 2);
	table->time_to_eat = ft_atosst(argv[3], 3);
	table->time_to_sleep = ft_atosst(argv[4], 4);
	if (argc == 6)
		table->nb_of_meal = ft_atosst(argv[5], 5);
	if (table->nb_of_philo == -1 || table->time_to_die == -1 || table->time_to_eat == -1 \
|| table->time_to_sleep == -1 || table->nb_of_meal == -1)
	{
		free(table);
		return (NULL);
	}
	return (table);
}
