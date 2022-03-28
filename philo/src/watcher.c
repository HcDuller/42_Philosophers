/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:07:27 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/24 17:27:33 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	check_starvation(t_table	*table, t_philo	*philosopher);
static void	*overwatcher(void	*arg);

void	start_watcher(t_table	*table)
{
	pthread_t	watcher;

	if (pthread_create(&watcher, NULL, &overwatcher, (void *)table))
	{
		write(STDERR_FILENO, "Could not create overwatcher.\n", 30);
		exit(EXIT_FAILURE);
	}
}

static void	check_starvation(t_table	*table, t_philo	*philosopher)
{
	unsigned long int	elapsed_meal_time;
	unsigned long int	elapsed_b_time;
	int					p_n;

	pthread_mutex_lock(&philosopher->self_lock);
	elapsed_meal_time = get_elapsed_ms(&philosopher->last_meal);
	elapsed_b_time = get_elapsed_ms(&(philosopher->base_time));
	pthread_mutex_unlock(&philosopher->self_lock);
	if (elapsed_meal_time > philosopher->starv_time_ms)
	{
		table->still_dining = 0;
		p_n = philosopher->vector_id + 1;
		printf("%06ld	%02d	died\n", elapsed_b_time, p_n);
		exit(EXIT_FAILURE);
	}
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
			check_starvation(table, table->philosophers + p_counter);
			p_counter++;
		}
		pthread_mutex_unlock(&table->self_lock);
		usleep(1000);
	}
	return (NULL);
}
