/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:17:31 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 01:22:49 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	philo_eat(t_table *table)
{
	print_msg("%06ld	%02d	is eating\n", table);
	usleep(table->eat_time_ms * 1000);
	return (1);
}

int	philo_sleep(t_table *table)
{
	print_msg("%06ld	%02d	is sleeping\n", table);
	usleep(table->sleep_time_ms * 1000);
	return (1);
}

int	philo_think(t_table *table)
{
	print_msg("%06ld	%02d	is thinking\n", table);
	usleep(100);
	return (1);
}
