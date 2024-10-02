/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:38:21 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/26 11:02:20 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_positive_num(const char *str)
{
	size_t	i;
	
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

ssize_t	ft_atosst(const char *str, size_t i)
{
	ssize_t	res;
	
	res = 0;
	if (ft_strlen(str) > 10)
		return (error_handle("Error: invalid argument\n", -1));
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > INT_MAX)
		return (error_handle("Error: argument max value is 2147483647\n", -1));
	if (i == 1 && (res == 0 || res > 200))
		return (error_handle("Error: The number of philosophers must be between 1 and 200\n", -1));
	else if (i > 1 && i < 5 && (res < 60))
		return (error_handle("Error: argument must be beween 60 and 2147483647\n", -1));
	return (res);
}


bool	parse_input(int argc, char **argv)
{
	size_t	i;

	i = 0;
	while (++i < (size_t)argc)
	{
		if (!is_positive_num(argv[i]))
		{	
			printf(RED"Error: Wrong format for argument %zu!\n"RST, i);
			return (false);
		}
	}
	return (true);
}