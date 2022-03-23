/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:54:11 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/23 17:06:16 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	eat_action(t_philo	*philosopher)
{
	unsigned long	eat_time;
	int				id;

	id = philosopher->vector_id + 1;
	if (philosopher->meals_left > 0)
		philosopher->meals_left--;
	eat_time = get_elapsed_ms(&(philosopher->base_time));
	printf("%08ld	[%02d]	is eating\n", eat_time, id);
	gettimeofday(&philosopher->last_meal, NULL);
	usleep(1000 * philosopher->eat_time_ms);
}

void	sleep_action(t_philo	*philosopher)
{
	unsigned long	el_time;
	int				id;

	id = philosopher->vector_id + 1;
	el_time = get_elapsed_ms(&(philosopher->base_time));
	printf("%08ld	[%02d]	is sleeping\n", el_time, id);
	usleep(1000 * philosopher->sleep_time_ms);
}

void	think_action(t_philo	*philosopher)
{
	unsigned long	el_time;
	int				id;

	id = philosopher->vector_id + 1;
	el_time = get_elapsed_ms(&(philosopher->base_time));
	printf("%08ld	[%02d]	is thinking\n", el_time, id);
}
