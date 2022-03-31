/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:12:42 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 21:33:51 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	simulating(t_table *table)
{
	int	running;

	if (try_wait(table->simulation_lock, table))
	{
		running = table->simulation->__align;
		sem_post(table->simulation_lock);
	}
	else
		running = 0;
	return (running);
}

void	end_simulation(t_table *table)
{
	if (try_wait(table->simulation_lock, table))
	{
		if (table->simulation->__align)
		{
			sem_wait(table->simulation);
		}
		sem_post(table->simulation_lock);
	}
}
