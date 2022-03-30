/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starvation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:15:19 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 13:28:49 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	starved_to_death(t_table *table)
{
	unsigned int	fasting_time;

	pthread_mutex_lock(&table->philosopher.self_lock);
	fasting_time = get_elapsed_ms(&table->philosopher.last_meal);
	pthread_mutex_unlock(&table->philosopher.self_lock);
	if (fasting_time > table->starv_time_ms)
	{
		pthread_mutex_lock(&table->philosopher.self_lock);
		table->philosopher.alive = 0;
		pthread_mutex_unlock(&table->philosopher.self_lock);
		print_msg("%06ld	%02d	died\n", table);
		end_simulation(table);
		return (1);
	}
	return (0);
}
