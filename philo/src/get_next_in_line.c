/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_in_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:21:06 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/31 14:21:18 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	get_next_in_line(t_philo *philosopher)
{
	int		next;

	next = philosopher->vector_id;
	if (philosopher->table->n_philosophers % 2)
	{
		next += 2;
		if (next > philosopher->table->n_philosophers - 1)
			next -= philosopher->table->n_philosophers;
	}
	else
	{
		if (next == philosopher->table->n_philosophers - 1)
			next = 0;
		else
		{
			next += 2;
			if (next > philosopher->table->n_philosophers - 1)
			{
				next -= philosopher->table->n_philosophers;
				next += 1;
			}
		}
	}
	return (next);
}
