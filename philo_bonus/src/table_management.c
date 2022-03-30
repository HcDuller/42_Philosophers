/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:59:15 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 16:49:33 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	set_up_table(t_table *table, unsigned int *args)
{
	ft_bzero(table, sizeof(t_table));
	table->n_philosophers = args[0];
	table->starv_time_ms = args[1];
	table->eat_time_ms = args[2];
	table->sleep_time_ms = args[3];
	table->meals = (int)args[4];
	table->procs = ft_calloc(args[0], sizeof(t_proc));
	table->philosopher.table = table;
	table->philosopher.alive = 1;
	gettimeofday(&table->base_time, NULL);
	table->philosopher.last_meal = table->base_time;
	pthread_mutex_init(&table->philosopher.self_lock, NULL);
	init_semaphores(table);
}

void	undo_table(t_table	*table)
{
	destroy_semaphores(table);
	pthread_mutex_destroy(&table->philosopher.self_lock);
	free(table->procs);
}

void	undo_child_table(t_table *table)
{
	close_semaphores(table);
	pthread_mutex_destroy(&table->philosopher.self_lock);
	free(table->procs);
}