/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:12:42 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/30 16:37:15 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	simulating(t_table *table)
{
	int	running;

	sem_wait(table->simulation_lock);
	running = table->simulation->__align;
	sem_post(table->simulation_lock);
	return (running);
}

void	end_simulation(t_table *table)
{
	sem_wait(table->simulation_lock);
	if (table->simulation->__align)
	{
		sem_wait(table->simulation);
	}
	sem_post(table->simulation_lock);
}
