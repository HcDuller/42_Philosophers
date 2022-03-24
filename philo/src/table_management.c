/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:49:47 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/23 21:26:02 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	init_philosophers(t_table *table, unsigned int *args);

void	alloc_table(t_table	*table, unsigned int *args)
{
	table->n_philosophers = args[0];
	table->forks = ft_calloc(args[0], sizeof(pthread_mutex_t));
	table->philosophers = ft_calloc(args[0], sizeof(t_philo));
	table->thread_counter = 0;
	table->still_dining = 1;
	if (pthread_mutex_init(&table->self_lock, NULL))
	{
		write(STDERR_FILENO, "Error: could not create mutex.\n", 31);
		exit(EXIT_FAILURE);
	}
	gettimeofday(&(table->base_time), NULL);
	init_philosophers(table, args);
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

void	init_philosophers(t_table *table, unsigned int *args)
{
	int	p_count;

	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		(table->philosophers + p_count)->table = table;
		(table->philosophers + p_count)->starv_time_ms = args[1];
		(table->philosophers + p_count)->eat_time_ms = args[2];
		(table->philosophers + p_count)->sleep_time_ms = args[3];
		if (args[4])
			(table->philosophers + p_count)->meals_left = args[4];
		else
			(table->philosophers + p_count)->meals_left = -1;
		if (pthread_mutex_init(table->forks + p_count, NULL))
		{
			write(STDERR_FILENO, "Error: could not create mutex.\n", 31);
			exit(EXIT_FAILURE);
		}
		p_count++;
	}
}
