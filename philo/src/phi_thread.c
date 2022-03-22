/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:58:10 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/22 15:47:14 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	pick_forks(t_philo	*philosopher);
static void	release_forks(t_philo	*philosopher);


void	*phi_thread(void *arg)
{
	t_philo	*philosopher;
	t_table	*table;
	
	table = (t_table *)arg;
	philosopher = table->philosophers + table->thread_counter;
	table->thread_counter++;
	pthread_mutex_unlock(&table->self_lock);
	while (philosophers_are_dinning(table))
	{
		pthread_mutex_lock(&philosopher->self_lock);
		if (philosopher->meals_left != 0)
		{
			pick_forks(philosopher);
			eat_action(philosopher);
			release_forks(philosopher);
			if (philosopher->meals_left == 0)
			{
				pthread_mutex_unlock(&philosopher->self_lock);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philosopher->self_lock);
		sleep_action(philosopher);
		think_action(philosopher);
	}
	return (NULL);
}

static void	pick_forks(t_philo	*philosopher)
{
	if (philosopher->vector_id % 2)
	{
		pthread_mutex_lock(philosopher->left_fork);
		printf("%08ld	[%02d]	has taken a fork(left)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
		pthread_mutex_lock(philosopher->right_fork);
		printf("%08ld	[%02d]	has taken a fork(right)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		printf("%08ld	[%02d]	has taken a fork(right)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
		pthread_mutex_lock(philosopher->left_fork);
		printf("%08ld	[%02d]	has taken a fork(left)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
	}
}

static void	release_forks(t_philo	*philosopher)
{
	pthread_mutex_unlock(philosopher->left_fork);
	printf("%08ld	[%02d]	released a fork(left)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
	pthread_mutex_unlock(philosopher->right_fork);
	printf("%08ld	[%02d]	released a fork(right)\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
}