/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:07:27 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/22 16:08:23 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	check_starvation(t_table	*table, t_philo	*philosopher);
static void	*overwatcher(void	*arg);

void	start_watcher(t_table	*table)
{
	pthread_t	watcher;

	if(pthread_create(&watcher,NULL, &overwatcher, (void *)table))
	{
		write(STDERR_FILENO,"Could not create overwatcher.\n",30);
		exit(EXIT_FAILURE);
	}
}

static void	check_starvation(t_table	*table, t_philo	*philosopher)
{
	unsigned long int	elapsed_meal_time;
	unsigned long int	elapsed_base_time;

	pthread_mutex_lock(&table->self_lock);
	pthread_mutex_lock(&philosopher->self_lock);
	elapsed_meal_time = get_elapsed_ms(&philosopher->last_meal);
	elapsed_base_time = get_elapsed_ms(&(philosopher->base_time));
	pthread_mutex_unlock(&philosopher->self_lock);
	if (elapsed_meal_time > philosopher->starv_time_ms)
	{
		table->still_dining = 0;
		printf("%08ld	[%02d]	died\n", elapsed_base_time, philosopher->vector_id + 1);
		pthread_mutex_unlock(&table->self_lock);
		exit(EXIT_FAILURE);
	}
	pthread_mutex_unlock(&table->self_lock);
}

static void	*overwatcher(void	*arg)
{
	t_table	*table;
	int		p_counter;

	table = (t_table *)arg;
	while (philosophers_are_dinning(table))
	{
		p_counter = 0;
		while (p_counter < table->n_philosophers)
		{
			check_starvation(table, table->philosophers + p_counter);
			p_counter++;
		}
	}
	return (NULL);
}
