/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:13:23 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/17 17:13:41 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (error_handle("Format: <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", 1));
    if (!parse_input(argc, argv))
        return (1);
    if (!init_all(argc, argv))
		return (1);
	return (0);
}

