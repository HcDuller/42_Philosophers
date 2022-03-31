/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:54:11 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 22:19:20 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	eat_action(t_philo	*philosopher)
{
	unsigned long	eat_time;
	int				id;

	if (!dinner_is_over(philosopher->table))
	{
		id = philosopher->vector_id + 1;
		pthread_mutex_lock(&philosopher->self_lock);
		if (philosopher->meals_left > 0)
			philosopher->meals_left--;
		eat_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%06ld	%02d	is eating\n", eat_time, id);
		gettimeofday(&philosopher->last_meal, NULL);
		pthread_mutex_unlock(&philosopher->self_lock);
		usleep(1000 * philosopher->eat_time_ms);
		return (1);
	}
	return (0);
}

int	sleep_action(t_philo	*philosopher)
{
	unsigned long	el_time;
	int				id;

	if (!dinner_is_over(philosopher->table))
	{
		id = philosopher->vector_id + 1;
		el_time = get_elapsed_ms(&(philosopher->base_time));
		printf("%06ld	%02d	is sleeping\n", el_time, id);
		usleep(1000 * philosopher->sleep_time_ms);
		return (1);
	}
	return (0);
}

int	think_action(t_philo	*philosopher)
{
	unsigned long	el_time;
	int				id;

	if (!dinner_is_over(philosopher->table))
	{
		id = philosopher->vector_id + 1;
		el_time = get_elapsed_ms(&(philosopher->base_time));
		usleep(100);
		printf("%06ld	%02d	is thinking\n", el_time, id);
		return (1);
	}
	return (0);
}
