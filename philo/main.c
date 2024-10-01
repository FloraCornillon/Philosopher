/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:23 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/25 17:46:21 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int res = 0;
// pthread_mutex_t mutex;

// void	*test(){
// 	for (int i = 0; i < 1000; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		res++;
// 		printf("res: %d\n", res);
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	return (NULL);
// }


int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (Error_handle("Format: <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", 1));
	t_table	*table;
	// t_philo *philo;
	size_t	i;
	
	i = 0;
	if (!Parse_input(argc, argv))
		return (1);
	table = Init_table(argc, argv);
	if (!table)
		return (1);
	free(table);
	return (0);
}

	//test
	// pthread_t philo[2]; //recuperer argv[1] avec atoi ou atol -> voir comment faire un tableau de structure
	// size_t i = 0;
	// pthread_mutex_init(&mutex, NULL);
	// while (i < 2) // i < argv[1]
	// {
	// 	if (pthread_create(philo + i, NULL, &test, NULL) != 0)
	// 	{
	// 		printf("Failed to create thread\n"); //ft_error?
	// 		return (1);
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (i < 2)
	// {
	// 	if (pthread_join(philo[i], NULL) != 0)
	// 	{
	// 		printf("Failed to join thread\n");
	// 		return (1);
	// 	}
	// 	i++;
	// }
	// printf("res: %d\n", res);
	// pthread_mutex_destroy(&mutex);