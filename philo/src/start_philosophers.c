/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:56:39 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/23 18:44:10 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	keep_creating(t_table *table);
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
	while (keep_creating(table))
	{
		pthread_mutex_lock(&table->self_lock);
		philo = table->philosophers + table->thread_counter;
		if (pthread_create(&(philo->thread), NULL, &phi_thread, (void *) table))
			exit(EXIT_FAILURE);
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

static int	keep_creating(t_table	*table)
{
	int	ok;

	ok = 0;
	pthread_mutex_lock(&table->self_lock);
	ok = table->thread_counter < table->n_philosophers;
	pthread_mutex_unlock(&table->self_lock);
	return (ok);
}
