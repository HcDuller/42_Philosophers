/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:47:57 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/22 16:09:19 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
	table->forks = ft_calloc(args[0], sizeof(pthread_mutex_t));
	table->philosophers = ft_calloc(args[0], sizeof(t_philo));
	table->thread_counter = 0;
	table->still_dining = 1;
	if (pthread_mutex_init( &table->self_lock, NULL))
	{
		write(STDERR_FILENO, "Error: could not create mutex.\n", 31);
		exit(EXIT_FAILURE);
	}
	gettimeofday(&(table->base_time), NULL);
	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		(table->philosophers + p_count)->starv_time_ms = args[1];
		(table->philosophers + p_count)->eat_time_ms = args[2];
		(table->philosophers + p_count)->sleep_time_ms = args[3];
		if (args[4])
			(table->philosophers + p_count)->meals_left = args[4];
		else
			(table->philosophers + p_count)->meals_left = -1;
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
	while (p_count < table->n_philosophers)
	{
		pthread_mutex_destroy(&(table->philosophers + p_count)->self_lock);
		pthread_mutex_destroy(table->forks + p_count);
		p_count++;
	}
	pthread_mutex_destroy(&table->self_lock);
	free(table->philosophers);
	free(table->forks);
}

void	wait_philosophers(t_table	*table)
{
	int		p_count;
	t_philo	*philo;

	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		usleep(1000);
		philo = table->philosophers + p_count;
		if (pthread_join(philo->thread, NULL))
			exit(EXIT_FAILURE);
		p_count++;
	}
}


int	main(int	argc, char	*argv[])
{
	unsigned int	args[5];
	t_table			table;

	eval_input(argc, argv);
	parse_params(argc, argv + 1, args);
	alloc_table(&table, args);
	start_philosophers(&table);
	start_watcher(&table);
	wait_philosophers(&table);
	free_table(&table);
	return (0);
}