/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:54:11 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/22 15:53:57 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	eat_action(t_philo	*philosopher)
{
	unsigned long	eat_time;

	if (philosopher->meals_left > 0)
		philosopher->meals_left--;
	eat_time = get_elapsed_ms(&(philosopher->base_time));
	printf("%08ld	[%02d]	is eating\n",	eat_time, philosopher->vector_id + 1);
	gettimeofday(&philosopher->last_meal, NULL);
	usleep(1000 * philosopher->eat_time_ms);
}

void	sleep_action(t_philo	*philosopher)
{
	printf("%08ld	[%02d]	is sleeping\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
	usleep(1000 * philosopher->sleep_time_ms);
}

void	think_action(t_philo	*philosopher)
{
	printf("%08ld	[%02d]	is thinking\n", get_elapsed_ms(&(philosopher->base_time)), philosopher->vector_id + 1);
}
