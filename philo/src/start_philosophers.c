/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:56:39 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/22 15:54:32 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	keep_creating(t_table	*table);

void	start_philosophers(t_table *table)
{
	int		p_count;
	t_philo	*philo;

	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		philo = table->philosophers + p_count;
		philo->vector_id = p_count;
		philo->left_fork = table->forks + p_count;
		philo->last_meal = table->base_time;
		philo->base_time = table->base_time;
		if (pthread_mutex_init(&philo->self_lock, NULL))
			exit(EXIT_FAILURE);
		if (p_count + 1 == table->n_philosophers)
			philo->right_fork = table->forks;
		else
			philo->right_fork = table->forks + p_count + 1;
		p_count++;
	}
	while (keep_creating(table))
	{
		pthread_mutex_lock(&table->self_lock);
		philo = table->philosophers + table->thread_counter;
		if (pthread_create(&(philo->thread), NULL, &phi_thread, (void *) table))
			exit(EXIT_FAILURE);
	}
}

static int	keep_creating(t_table	*table)
{
	int	ok;

	ok = 0;
	pthread_mutex_lock(&table->self_lock);
	ok = table->thread_counter < table->n_philosophers;
	pthread_mutex_unlock(&table->self_lock);
	return (ok);
}
