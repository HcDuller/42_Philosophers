/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:47:57 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/16 20:16:00 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //memset

typedef	struct s_philo_thread
{
	pthread_t		thread;
	int				phi_id;
	unsigned int	starv_time_ms;
	unsigned int	sleep_time_ms;
	unsigned int	eat_time_ms;
	unsigned int	able_to_eat;

} t_philo_thread;
/*
	1000 microsecond = 1 milisecond
*/

void	validate_argc(int	argc)
{
	if (argc < 5)
	{
		write(STDIN_FILENO,"Too few arguments\n", 18);
		exit(EXIT_FAILURE);
	}
	else if (argc > 6)
	{
		write(STDIN_FILENO,"Too many arguments\n", 19);
		exit(EXIT_FAILURE);
	}
}

int	is_digit(char	c)
{
	if ((int)c >= 48 || (int)c <= 57)
		return (1);
	return (0);
}

void	validate_argv(char **argv)
{
	int	i;
	int	c_i;

	i = 1;
	while (argv[i])
	{
		c_i = 0;
		while (argv[i][c_i])
		{
			if (!is_digit(argv[i][c_i]))
			{
				write(STDERR_FILENO, "Only numeric ", 13);
				write(STDERR_FILENO, "parameters are allowed\n", 23);
				exit(EXIT_FAILURE);
			}
			c_i++;
		}
		i++;
	}
}
/*
unsigned int	tenth_power(unsigned int pow)
{
	unsigned	int	final_value;

	final_value = 1;
	while (pow > 0)
	{
		final_value *= 10;
		pow--;
	}
	return	(final_value);
}
*/
unsigned int	str_to_uint(char *str)
{
	int	i;
	unsigned int	value;
	unsigned int	pow;

	i = 0;
	value = 0;
	pow = 1;
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		value += (((int) str[i]) - 48) * pow;
		i--;
		pow *= 10;
	}
	return (value);
}

int	*parse_params(int	argc, char *argv[])
{
	int	*i_argv;


}

int	main(int	argc, char	*argv[])
{
	unsigned int	*i_argv;

	validate_argc(argc);
	validate_argv(argv);
	return (0);
}