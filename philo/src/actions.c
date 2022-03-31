/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:54:11 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/31 14:27:48 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	eat_action(t_philo	*philosopher)
{
	if (!dinner_is_over(philosopher->table))
	{
		pthread_mutex_lock(&philosopher->self_lock);
		if (philosopher->meals_left > 0)
			philosopher->meals_left--;
		print_msg("%06ld	%02d	is eating\n", philosopher);
		gettimeofday(&philosopher->last_meal, NULL);
		pthread_mutex_unlock(&philosopher->self_lock);
		usleep(1000 * philosopher->eat_time_ms);
		return (1);
	}
	return (0);
}

int	sleep_action(t_philo	*philosopher)
{
	if (!dinner_is_over(philosopher->table))
	{
		print_msg("%06ld	%02d	is sleeping\n", philosopher);
		usleep(1000 * philosopher->sleep_time_ms);
		return (1);
	}
	return (0);
}

int	think_action(t_philo	*philosopher)
{
	if (!dinner_is_over(philosopher->table))
	{
		print_msg("%06ld	%02d	is thinking\n", philosopher);
		return (1);
	}
	return (0);
}
