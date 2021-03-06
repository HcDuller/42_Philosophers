/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:29:48 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 21:37:41 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	init_semaphores(t_table *table)
{
	int	options;

	options = S_IRUSR | S_IWUSR;
	sem_unlink("/forks");
	sem_unlink("/fork_lock");
	sem_unlink("/hands_lock");
	sem_unlink("/simulation");
	sem_unlink("/simulation_lock");
	sem_unlink("/die_lock");
	table->forks = sem_open("/forks", O_CREAT, options, table->n_philosophers);
	table->fork_lock = sem_open("/fork_lock", O_CREAT, options, 1);
	table->hands_lock = sem_open("/hands_lock", O_CREAT, options, 1);
	table->simulation = sem_open("/simulation", O_CREAT, options, 1);
	table->simulation_lock = sem_open("/simulation_lock", O_CREAT, options, 1);
	table->die_lock = sem_open("/die_lock", O_CREAT, options, 1);
}

void	destroy_semaphores(t_table *table)
{
	close_semaphores(table);
	unlink_semaphores();
}

void	close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->fork_lock);
	sem_close(table->simulation);
	sem_close(table->hands_lock);
	sem_close(table->simulation_lock);
	sem_close(table->die_lock);
}

void	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/fork_lock");
	sem_unlink("/hands_lock");
	sem_unlink("/simulation");
	sem_unlink("/simulation_lock");
	sem_unlink("/die_lock");
}
