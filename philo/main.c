/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:47:57 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/17 20:21:49 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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

int	is_digit(int	c)
{
	if (c >= 48 && c <= 57)
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

void	parse_params(int	argc, char *argv[], unsigned int	*i_args)
{
	unsigned int	i;
	unsigned int	u_argc;

	u_argc = (unsigned int)argc - 1;
	ft_bzero(i_args, 5 * sizeof(unsigned int));
	i = 0;
	while(i < u_argc)
	{
		i_args[i] = str_to_uint(*(argv + i));
		i++;
	}
}

void	alloc_table(t_table	*table, unsigned int *args)
{
	int	p_count;

	table->n_philosophers = args[0];
	table->starv_time_ms = args[1];
	table->eat_time_ms = args[2];
	table->sleep_time_ms = args[3];
	table->forks = ft_calloc(args[0], sizeof(pthread_mutex_t));
	table->philosophers = ft_calloc(args[0], sizeof(t_philo));
	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		if (pthread_mutex_init( table->forks + p_count, NULL))
		{
			write(STDERR_FILENO, "Error: could not create mutex.\n", 31);
			exit(EXIT_FAILURE);
		}
		p_count++;
	}
}

void	free_table(t_table *table)
{
	int	p_count;

	p_count = 0;
	free(table->philosophers);
	while (p_count < table->n_philosophers)
	{
		pthread_mutex_destroy(table->forks + p_count);
	}
	free(table->forks);
}

void	start_philosophers(t_table *table)
{
	int		p_count;
	t_philo	*philo;

	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		philo = table->philosophers + p_count;
		philo->vector_id = p_count;
		philo->str_id = ft_itoa(p_count);
		philo->left_fork = table->forks + p_count;
		if (p_count + 1 == table->n_philosophers)
			philo->right_fork = table->forks;
		else
			philo->right_fork = table->forks + p_count + 1;
		p_count++;
	}
	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		philo = table->philosophers;
		p_count++;
	}
}

int	main(int	argc, char	*argv[])
{
	unsigned int	args[5];
	t_table			table;

	validate_argc(argc);
	validate_argv(argv);
	parse_params(argc, argv + 1, args);
	alloc_table(&table, args);
	start_philosophers(&table);
	free_table(&table);
	return (0);
}