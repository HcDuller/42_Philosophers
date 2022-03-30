/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:17:31 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 17:09:39 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	philo_eat(t_table *table)
{
	if (simulating(table) && is_alive(table))
	{
		pthread_mutex_lock(&table->philosopher.self_lock);
		gettimeofday(&table->philosopher.last_meal, NULL);
		pthread_mutex_unlock(&table->philosopher.self_lock);
		print_msg("%06ld	%02d	is eating\n", table);
		usleep(table->eat_time_ms * 1000);
		return (1);
	}
	return (0);
}

int	philo_sleep(t_table *table)
{
	if (simulating(table) && is_alive(table))
	{
		print_msg("%06ld	%02d	is sleeping\n", table);
		usleep(table->sleep_time_ms * 1000);
		return (1);
	}
	return (0);
}

int	philo_think(t_table *table)
{
	if (simulating(table) && is_alive(table))
	{
		print_msg("%06ld	%02d	is thinking\n", table);
		usleep(100);
		return (1);
	}
	return (0);
}
