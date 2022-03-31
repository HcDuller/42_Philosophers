/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:07:27 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/31 14:36:59 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	philosopher_starved(t_table	*table, t_philo	*philosopher);
static void	*overwatcher(void	*arg);

void	start_watcher(t_table	*table)
{
	pthread_t	watcher;

	if (pthread_create(&watcher, NULL, &overwatcher, (void *)table))
	{
		write(STDERR_FILENO, "Could not create overwatcher.\n", 30);
		exit(EXIT_FAILURE);
	}
	pthread_join(watcher, NULL);
}

static int	philosopher_starved(t_table	*table, t_philo	*philosopher)
{
	unsigned long int	elapsed_meal_time;

	pthread_mutex_lock(&philosopher->self_lock);
	elapsed_meal_time = get_elapsed_ms(&philosopher->last_meal);
	pthread_mutex_unlock(&philosopher->self_lock);
	if (elapsed_meal_time > philosopher->starv_time_ms)
	{
		table->still_dining = 0;
		print_msg("%06ld	%02d	died\n", philosopher);
		return (1);
	}
	return (0);
}

static void	*overwatcher(void	*arg)
{
	t_table	*table;
	int		p_counter;

	table = (t_table *)arg;
	while (philosophers_are_dinning(table))
	{
		p_counter = 0;
		pthread_mutex_lock(&table->self_lock);
		while (p_counter < table->n_philosophers)
		{
			if (philosopher_starved(table, table->philosophers + p_counter))
			{
				pthread_mutex_unlock(&table->self_lock);
				return (NULL);
			}
			p_counter++;
		}
		pthread_mutex_unlock(&table->self_lock);
		usleep(100);
	}
	return (NULL);
}
