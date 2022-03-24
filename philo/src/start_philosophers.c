/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:56:39 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/24 14:03:14 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	initialize_philosopher(t_table *table, int pos);

void	start_philosophers(t_table *table)
{
	int		p_count;
	t_philo	*philo;

	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		initialize_philosopher(table, p_count);
		p_count++;
	}
	p_count = 0;
	while (p_count < table->n_philosophers)
	{
		philo = table->philosophers + p_count;
		if (pthread_create(&(philo->thread), NULL, &phi_thread, (void *) philo))
			exit(EXIT_FAILURE);
		p_count++;
	}
}

static void	initialize_philosopher(t_table *table, int pos)
{
	t_philo	*philo;

	philo = table->philosophers + pos;
	if (pthread_mutex_init(&philo->self_lock, NULL))
		exit(EXIT_FAILURE);
	philo->vector_id = pos;
	philo->last_meal = table->base_time;
	philo->base_time = table->base_time;
	philo->left_fork = table->forks + pos;
	if (pos + 1 == table->n_philosophers)
		philo->right_fork = table->forks;
	else
		philo->right_fork = table->forks + pos + 1;
}
