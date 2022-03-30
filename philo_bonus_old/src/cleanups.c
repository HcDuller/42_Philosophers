/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:02:20 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 19:21:15 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->fork_lock);
	sem_close(table->a_philo_died);
	sem_close(table->simulation);
	sem_close(table->simulation_lock);
	sem_close(table->print_lock);
	sem_unlink("/forks");
	sem_unlink("/fork_lock");
	sem_unlink("/philos_dead");
	sem_unlink("/simulation");
	sem_unlink("/simulation_lock");
	sem_unlink("/print");
}

void	clean_up(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
	close_semaphores(table);
}

void	forked_cleanup(t_philo *philosopher)
{
	t_table			*table;
	t_philo			*tmp_philo;
	unsigned int	p;

	table = philosopher->table;
	p = 0;
	while (p < table->n_philosophers &&  table->philosophers + p < philosopher)
	{
		tmp_philo = table->philosophers + p;
		pthread_mutex_destroy(&tmp_philo->self_lock);
		p++;
	}
	pthread_mutex_destroy(&philosopher->self_lock);
	close_semaphores(table);
	free(table->philosophers);
}