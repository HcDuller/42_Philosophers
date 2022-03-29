/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:30:01 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 16:37:22 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	release_forks(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	char			*msg;
	t_table			*table;

	pthread_mutex_lock(&philosopher->self_lock);
	if (philosopher->alive)
	{
		sem_wait(philosopher->table->print_lock);
		msg = "%06ld	%02d	has released a fork\n";
		table = philosopher->table;
		sem_post(table->forks);
		ellapsed_time = get_elapsed_ms(&table->base_time);
		printf(msg, ellapsed_time, philosopher->p_number);
		sem_post(table->forks);
		ellapsed_time = get_elapsed_ms(&table->base_time);
		printf(msg, ellapsed_time, philosopher->p_number);
		sem_post(philosopher->table->print_lock);
	}
	pthread_mutex_unlock(&philosopher->self_lock);
	
}

int	pick_forks(t_philo *philosopher)
{
	unsigned long	ellapsed_time;
	t_table			*table;
	char			*msg;

	pthread_mutex_lock(&philosopher->self_lock);
	if (philosopher->alive)
	{
		table = philosopher->table;
		msg = "%06ld	%02d	has taken a fork\n";
		sem_wait(table->forks);
		sem_wait(philosopher->table->print_lock);
		ellapsed_time = get_elapsed_ms(&table->base_time);
		printf(msg, ellapsed_time, philosopher->p_number);
		sem_post(philosopher->table->print_lock);
		sem_wait(table->forks);
		sem_wait(philosopher->table->print_lock);
		ellapsed_time = get_elapsed_ms(&table->base_time);
		printf(msg, ellapsed_time, philosopher->p_number);
		sem_post(philosopher->table->print_lock);
	}
	pthread_mutex_unlock(&philosopher->self_lock);
}
