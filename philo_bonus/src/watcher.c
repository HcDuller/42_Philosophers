/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:28:21 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 00:22:36 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

static int	philosopher_starved(t_philo	*philosopher, t_table	*table);
static int	philosopher_satisfied(t_philo	*philosopher);

void *watcher(void *arg)
{
	t_philo	*philosopher;
	t_table	*table;

	philosopher = (t_philo *)arg;
	table = philosopher->table;
	while (!philosopher_satisfied(philosopher))
	{
		if (philosopher_starved(philosopher, table))
			exit(EXIT_FAILURE); //possibly needs cleanup here.
		usleep(1000);
	}
	return	(NULL);
}

static int	philosopher_satisfied(t_philo	*philosopher)
{
	int	ret_value;

	pthread_mutex_lock(&philosopher->self_lock);
	if (philosopher->meals_left == 0)
		ret_value = 1;
	else
		ret_value = 0;
	pthread_mutex_unlock(&philosopher->self_lock);
	return (ret_value);
}

static int	philosopher_starved(t_philo	*philosopher, t_table	*table)
{
	unsigned long int	elapsed_meal_time;
	unsigned long int	elapsed_b_time;
	int					ret_value;

	pthread_mutex_lock(&philosopher->self_lock);
	elapsed_meal_time = get_elapsed_ms(&philosopher->last_meal);
	if (elapsed_meal_time > table->starv_time_ms)
	{
		elapsed_b_time = get_elapsed_ms(&(table->base_time));
		ret_value = 1;
		printf("%06ld	%02d	died\n", elapsed_b_time, philosopher->p_number);
	}
	else
		ret_value = 0;
	pthread_mutex_unlock(&philosopher->self_lock);
	return (ret_value);
}