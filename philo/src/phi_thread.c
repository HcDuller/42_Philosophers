/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:58:10 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/23 19:07:57 by hde-camp         ###   ########.fr       */
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
		if (philosopher->meals_left != 0)
		{
			pick_forks(philosopher);
			eat_action(philosopher);
			release_forks(philosopher);
			if (philosopher->meals_left == 0)
			{
				return (NULL);
			}
		}
		sleep_action(philosopher);
		think_action(philosopher);
	}
	return (NULL);
}

static void	pick_forks(t_philo	*philosopher)
{
	int				id;
	unsigned long	l_time;
	unsigned long	r_time;

	id = philosopher->vector_id + 1;
	if (philosopher->vector_id % 2)
	{
		printf("%08ld	[%02d]	trying to pick a fork(left hand)\n", get_elapsed_ms(&(philosopher->base_time)), id);
		pthread_mutex_lock(philosopher->left_fork);
		l_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	has taken a fork(left)\n", l_time, id);
		printf("%08ld	[%02d]	trying to pick a fork(right hand)\n", get_elapsed_ms(&(philosopher->base_time)), id);
		pthread_mutex_lock(philosopher->right_fork);
		r_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	has taken a fork(right)\n", r_time, id);
	}
	else
	{
		printf("%08ld	[%02d]	trying to pick a fork(right hand)\n", get_elapsed_ms(&(philosopher->base_time)), id);
		pthread_mutex_lock(philosopher->right_fork);
		r_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	has taken a fork(right)\n", r_time, id);
		printf("%08ld	[%02d]	trying to pick a fork(left hand)\n", get_elapsed_ms(&(philosopher->base_time)), id);
		pthread_mutex_lock(philosopher->left_fork);
		l_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	has taken a fork(left)\n", l_time, id);
	}
}

static void	release_forks(t_philo	*philosopher)
{
	int				id;
	unsigned long	l_time;
	unsigned long	r_time;

	id = philosopher->vector_id + 1;
	if (philosopher->vector_id % 2)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		l_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	released a fork(left)\n", l_time, id);
		pthread_mutex_unlock(philosopher->right_fork);
		r_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	released a fork(right)\n", r_time, id);
	}
	else
	{
		pthread_mutex_unlock(philosopher->right_fork);
		r_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	released a fork(right)\n", r_time, id);
		pthread_mutex_unlock(philosopher->left_fork);
		l_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%08ld	[%02d]	released a fork(left)\n", l_time, id);
	}
}
