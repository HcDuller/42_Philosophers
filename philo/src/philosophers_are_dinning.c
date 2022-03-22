/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_are_dinning.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:59:30 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/22 14:34:49 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int		philosophers_are_dinning(t_table	*table)
{
	int	ok;
	int	p_counter;
	int	meals_left;

	p_counter = 0;
	pthread_mutex_lock(&table->self_lock);
	ok = 0;
	if (table->still_dining)
	{
		while (p_counter < table->n_philosophers)
		{
			meals_left = (table->philosophers + p_counter)->meals_left;
			if (meals_left == -1 || meals_left > 0)
				ok = 1;
			p_counter++;
		}
	}
	pthread_mutex_unlock(&table->self_lock);
	return (ok);
}
