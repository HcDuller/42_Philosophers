/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:28:21 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/29 14:15:57 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

static int	philosopher_starved(t_philo *philosopher, t_table *table);
static int	philosopher_satisfied(t_philo *philosopher);
static void	handle_death(t_philo *philosopher, t_table *table);

void	*watcher(void *arg)
{
	int					dead_philo;
	t_philo				*philosopher;
	t_table				*table;

	philosopher = (t_philo *)arg;
	table = philosopher->table;
	while (!philosopher_satisfied(philosopher))
	{
		dead_philo = philosopher_starved(philosopher, table);
		dead_philo |= (table->a_philo_died->__align == 0);
		if (dead_philo)
		{
			handle_death(philosopher, table);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	handle_death(t_philo *philosopher, t_table *table)
{
	unsigned long int	elapsed_b_time;

	if (table->a_philo_died->__align)
	{
		sem_wait(table->a_philo_died);
		elapsed_b_time = get_elapsed_ms(&(table->base_time));
		printf("%06ld	%02d	died\n", elapsed_b_time, philosopher->p_number);
	}
	exit(EXIT_FAILURE);
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
	int					ret_value;

	pthread_mutex_lock(&philosopher->self_lock);
	elapsed_meal_time = get_elapsed_ms(&philosopher->last_meal);
	if (elapsed_meal_time > table->starv_time_ms)
	{
		ret_value = 1;
	}
	else
		ret_value = 0;
	pthread_mutex_unlock(&philosopher->self_lock);
	return (ret_value);
}
